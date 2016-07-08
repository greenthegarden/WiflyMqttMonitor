#ifndef WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_
#define WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_


#define USE_HARDWARE_WATCHDOG       false


#if USE_HARDWARE_WATCHDOG

const int RESET_WATCHDOG_PIN          = 10;
unsigned long previousMillis          = 0UL;
const unsigned long WATCHDOG_INTERVAL = 60UL * 1000UL;

void ResetWatchdog()
{
 pinMode(RESET_WATCHDOG_PIN, OUTPUT);
 delay(200);
 pinMode(RESET_WATCHDOG_PIN, INPUT);
 DEBUG_LOG(2, "Watchdog Reset");
}

#endif


#endif  /* WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_ */

