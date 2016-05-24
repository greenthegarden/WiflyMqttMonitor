#ifndef WIFLYMQTTMONITOR_NETWORK_CONFIG_H_
#define WIFLYMQTTMONITOR_NETWORK_CONFIG_H_


#define USE_SECURE_NETWORK   true

// Wifi parameters
const char SSID[]          = "videoAtHome";
#if USE_SECURE_NETWORK
const char PASSPHRASE[]    = "Cambridge&";
boolean    mode            = true; //or WEP_MODE
#endif


#endif  /* WIFLYMQTTMONITOR_NETWORK_CONFIG_H_ */

