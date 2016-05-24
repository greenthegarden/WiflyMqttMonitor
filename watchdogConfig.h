#ifndef WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_
#define WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_


#define USE_HARDWARE_WATCHDOG       false


#if USE_HARDWARE_WATCHDOG

const int RESET_WATCHDOG1             = 10;
unsigned long previousMillis          = 0UL;
const unsigned long watchdog_interval = 60UL * 1000UL;

void ResetWatchdog1()
{
 pinMode(RESET_WATCHDOG1, OUTPUT);
 delay(200);
 pinMode(RESET_WATCHDOG1, INPUT);
 DEBUG_LOG(2, "Watchdog1 Reset");
}

#endif


#endif  /* WIFLYMQTTMONITOR_WATCHDOG_CONFIG_H_ */

