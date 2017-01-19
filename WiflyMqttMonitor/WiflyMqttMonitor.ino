#include <Arduino.h>

#include "config.h"

typedef enum {
  WIRE_SHORTED = 0,
  NORMAL       = 1,
  TRIGGERED    = 2,
  TAMPERED     = 3,
} sensorStates_t;

void callback(char* topic, uint8_t* payload, unsigned int length)
{
  // handle message arrived
  /* topic = part of the variable header:has topic name of the topic where the publish received
   	  NOTE: variable header does not contain the 2 bytes with the
   	        publish msg ID
   	  payload = pointer to the first item of the buffer array that
   	            contains the message tha was published
   	           EXAMPLE of payload: lights,1
   	  length = the length of the payload, until which index of payload
  */

  DEBUG_LOG(1, "Payload length is");
  DEBUG_LOG(1, length);

  // Copy the payload to the new buffer
  char* message = (char*)malloc((sizeof(char) * length) + 1); // get the size of the bytes and store in memory
  memcpy(message, payload, length * sizeof(char));        // copy the memory
  message[length * sizeof(char)] = '\0';                  // add terminating character

  DEBUG_LOG(1, "Message with topic");
  DEBUG_LOG(1, topic);
  DEBUG_LOG(1, "arrived with payload");
  DEBUG_LOG(1, message);

  byte topic_idx = 0;
  // find if topic is matched
  for (byte i = 0; i < ARRAY_SIZE(SUBSCRIPTION_TOPICS); i++) {
    progBuffer[0] = '\0';
    strcpy_P(progBuffer, (PGM_P)pgm_read_word(&(SUBSCRIPTION_TOPICS[i])));
    if (strcmp(topic, progBuffer) == 0) {
      topic_idx = i;
      break;
    }
  }

  if (topic_idx == 0) {  // topic is SECURITY_TOPIC
    DEBUG_LOG(1, "SECURITY_TOPIC topic arrived");
    char* separator = strchr(message, COMMAND_SEPARATOR);
    DEBUG_LOG(1, "separator: ");
    DEBUG_LOG(1, separator);
    if (separator != 0) {
      //      byte sensorRef = atoi(message);
      const char sensorRef = message[0];
      DEBUG_LOG(1, "sensorRef: ");
      DEBUG_LOG(1, sensorRef);
      if (strcmp(sensorRef, 'D') == 0) {
        ++separator;
        byte sensorState = atoi(separator);
        DEBUG_LOG(1, "sensorState: ");
        DEBUG_LOG(1, sensorState);
        if (sensorState == TRIGGERED) {
          // alarm triggered
          if (!alarmSounding) {
            soundAlarm = true;
            DEBUG_LOG(1, "sound alarm!!");
          }
        } else {
          soundAlarm = false;
        }
      }
    }
  } else if (topic_idx == 1) {
    DEBUG_LOG(1, "ALARM_TOPIC topic arrived");
    if (strcmp(message, "1") == 0) {
      if (!alarmSounding) {
        soundAlarm = true;
        DEBUG_LOG(1, "sound alarm!!");
      }
    } else {
      soundAlarm = false;
    }
  }

  // free memory assigned to message
  free(message);
}

boolean mqtt_connect()
{
  DEBUG_LOG(1, "Attempting MQTT connection ...");
  if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
    DEBUG_LOG(1, "  connected");
    // Once connected, publish an announcement ...
    publish_connected();
    //    publish_ip_address();
    // ... and subscribe to topics (should have list)
    //  mqttClient.subscribe("homesecurity/status/sensor");
    //  mqttClient.subscribe("homesecurity/interior/status/sensor");
    mqttClient.subscribe("interiorhs/status/sensor");
    mqttClient.subscribe("home/security/alarm");
  } else {
    DEBUG_LOG(1, "failed, rc = ");
    DEBUG_LOG(1, mqttClient.state());
  }
  return mqttClient.connected();
}

void reset_connection()
{
  if (mqttClient.connected())
    mqttClient.disconnect();
  wifly_connect();
  mqtt_connect();
}

/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(BAUD_RATE);

  Serial.println("Test");

  // Configure WiFly
  DEBUG_LOG(1, "configuring WiFly ...");
  wifly_configure();

  DEBUG_LOG(1, "connecting WiFly ...");
  wifly_connect();

#if USE_HARDWARE_WATCHDOG
  ResetWatchdog();
#endif
}


/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
  --------------------------------------------------------------------------------------*/
void loop()
{
  unsigned long now = millis();

  // require a client.loop in order to receive subscriptions
  //  mqttClient.loop();

  //  if (!mqtt_client.loop()) {
  //    mqtt_connect();
  //  }

  // alternative based on code in relayr
  // if (mqttClient.connected()) {
  //   mqttClient.loop();
  // } else {
  //   //if connection lost, try to reconnect
  //   mqtt_connect();
  // }

  if (!mqttClient.connected()) {
    mqttClientConnected = false;
    if (now - lastReconnectAttempt >= RECONNECTION_ATTEMPT_INTERVAL) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (mqtt_connect()) {
        lastReconnectAttempt = 0;
        mqttClientConnected = true;
      }
    }
  } else {
    // Client connected
    mqttClient.loop();
  }

  if (soundAlarm && !alarmSounding) {
    alarmStart = now;
    alarmSounding = true;
    DEBUG_LOG(1, "alarmStart set");
  }

  if (alarmSounding && (now - alarmStart <= ALARM_DURATION)) {
    DEBUG_LOG(1, "alertTone");
    alertTone();
  }

  if (alarmSounding && (now - alarmStart > ALARM_DURATION)) {
    DEBUG_LOG(1, "stop alert");
    soundAlarm = false;
    alarmSounding = false;
    //    alarmStart = 0UL;
  }

#if USE_HARDWARE_WATCHDOG
  if (now - previousMillis >= WATCHDOG_INTERVAL) {
    // save the last time you blinked the LED
    previousMillis = now;
    ResetWatchdog();
  }
#endif
}
