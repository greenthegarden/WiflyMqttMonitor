#ifndef WIFLYMQTTMONITOR_WIFLY_CONFIG_H_
#define WIFLYMQTTMONITOR_WIFLY_CONFIG_H_

/* 
 * RN-XV WiFly Module - Wire Antenna
 * MAC: 00:06:66:50:71:6f
 * IP: 192.168.1.52
 *  
 * RN-XV WiFly Module – SMA
 * MAC: 00:06:66:71:68:d5
 * IP: 192.168.1.51
 */

/* 
 * WiFly configuration
 * 
 * reboot	
 * $$$	
 * factory RESET	
 * 	
 * set wlan join 0    // Stop device connecting while we setup
 * 
 * set ip dhcp 1
 * set wlan ssid xxx
 * set wlan phrase xxx
 * set wlan join 1
 * 
 * save
 * reboot
 */

#include <SoftwareSerial.h>

const byte WIFLY_SERIAL_RX        = 11;
const byte WIFLY_SERIAL_TX        = 12;

SoftwareSerial wifly_serial(WIFLY_SERIAL_RX, WIFLY_SERIAL_TX);

// WiFly libraries
#include <SPI.h>
#include <WiFly.h>

#include "networkConfig.h"

boolean wiflyConnected = false;

WiFlyClient    wiflyClient;

void wifly_configure()
{
  wifly_serial.begin(BAUD_RATE);      // Start software serial for the RN-XV
  WiFly.setUart(&wifly_serial);
}

byte wifly_connect()
{
#if USE_STATUS_LED
  digitalWrite(STATUS_LED, HIGH);
#endif

  DEBUG_LOG(1, "initialising wifly");

  WiFly.begin();
  delay(5000);  // time for WiFly to start

  DEBUG_LOG(1, "joining network");

  if (!WiFly.join(SSID, PASSPHRASE, mode)) {
    wiflyConnected = false;
    DEBUG_LOG(1, "  connection failed");
  } else {
    wiflyConnected = true;
    DEBUG_LOG(1, "  connected");
#if USE_STATUS_LED
    digitalWrite(STATUS_LED, LOW);
#endif
    return 1;
  }
  return 0;
}

byte wifly_disconnect()
{
  if (wiflyConnected) {
    WiFly.leave();
    wiflyConnected = false;
    return 1;
  }
  return 0;
}

//void wifly_sleep()
//{
//  wifly_disconnect();
//  
//  DEBUG_LOG(1, "WiFly: setting sleep timer");
//  WiFly.setSleepTimer(10);
//
//  DEBUG_LOG(1, "WiFly: setting wake timer");
//  WiFly.setWakeTimer(MEASUREMENT_INTERVAL_SECS - 20);
//}


#endif  /* WIFLYMQTTMONITOR_WIFLY_CONFIG_H_ */

