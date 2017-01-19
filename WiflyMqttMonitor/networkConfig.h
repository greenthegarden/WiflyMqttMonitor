#ifndef WIFLYMQTTMONITOR_NETWORK_CONFIG_H_
#define WIFLYMQTTMONITOR_NETWORK_CONFIG_H_


#define USE_SECURE_NETWORK   true

// Wifi parameters
const char SSID[]          = "videoAtHome-2.4g";
#if USE_SECURE_NETWORK
const char PASSPHRASE[]    = "C@mbridge&";
boolean    mode            = true; //or WEP_MODE
#endif


#endif  /* WIFLYMQTTMONITOR_NETWORK_CONFIG_H_ */

