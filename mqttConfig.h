#ifndef WIFLYMQTTMONITOR_MQTT_CONFIG_H_
#define WIFLYMQTTMONITOR_MQTT_CONFIG_H_


#include <PubSubClient.h>


// MQTT parameters
IPAddress mqttServerAddr(192, 168, 1, 50);    // openHAB server
char mqttClientId[]               = "monitor";
const int MQTT_PORT               = 1883;
//#define MQTT_MAX_PACKET_SIZE        168
//#define MQTT_KEEPALIVE              300

const char COMMAND_SEPARATOR      = ',';

// callback
void callback(char* topic, uint8_t* payload, unsigned int length);

PubSubClient mqttClient(mqttServerAddr, MQTT_PORT, callback, wiflyClient);


// MQTT topic definitions

const char WIFLY_STATUS[]      PROGMEM = "monitor/status/wifly";
const char UPTIME_STATUS[]     PROGMEM = "monitor/status/uptime";
const char MEMORY_STATUS[]     PROGMEM = "monitor/status/memory";

PGM_P const STATUS_TOPICS[]    PROGMEM = { WIFLY_STATUS,     // idx = 0
                                           UPTIME_STATUS,    // idx = 1
                                           MEMORY_STATUS,    // idx = 2
                                          };

// MQTT payloads
const char MQTT_PAYLOAD_CONNECTED[]   PROGMEM = "CONNECTED";
const char MQTT_PAYLOAD_ERROR[]       PROGMEM = "ERROR";
const char MQTT_PAYLOAD_START[]       PROGMEM = "START";
const char MQTT_PAYLOAD_END[]         PROGMEM = "END";

PGM_P const MQTT_PAYLOADS[]           PROGMEM = { MQTT_PAYLOAD_CONNECTED,   // idx = 0
                                                  MQTT_PAYLOAD_ERROR,       // idx = 1
                                                  MQTT_PAYLOAD_START,       // idx = 2
                                                  MQTT_PAYLOAD_END,         // idx = 3
                                                };

// subscription topics
//const char SECURITY_TOPIC[]    PROGMEM = "homesecurity/status/sensor";
const char SECURITY_TOPIC[]    PROGMEM = "interiorhs/status/sensor";
//const char SECURITY_TOPIC[]    PROGMEM = "homesecurity/interior/status/sensor";

PGM_P const SUBSCRIPTION_TOPICS[]   PROGMEM = { SECURITY_TOPIC,    // idx = 0
                                              };

void publish_connected()
{
  messBuffer[0] = '\0';
  strcpy_P(messBuffer, (char*)pgm_read_word(&(MQTT_PAYLOADS[0])));
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[0])));
  mqttClient.publish(progBuffer, messBuffer);
}

void publish_ip_address()
{
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[1])));
  mqttClient.publish(progBuffer, "192.168.1.90");
}

void publish_uptime()
{
  messBuffer[0] = '\0';
  ltoa(millis(), messBuffer, 10);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[2])));
  mqttClient.publish(progBuffer, messBuffer);
}


#endif  /* WIFLYMQTTMONITOR_MQTT_CONFIG_H_ */

