#ifndef WIFLYMQTTMONITOR_CONFIG_H_
#define WIFLYMQTTMONITOR_CONFIG_H_


#include "debug.h"


const byte BUFFER_SIZE            = 32;
char progBuffer[BUFFER_SIZE];
char messBuffer[BUFFER_SIZE];

// Macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


const int AFTER_ERROR_DELAY       = 1000;


// Serial parameters
const int BAUD_RATE               = 9600;


const byte LED_PIN                = 13;


#include <MemoryFree.h>


// Watchdog configuration
#include "watchdogConfig.h"


#include "wiFlyConfig.h"
#include "mqttConfig.h"

#include "oledShieldConfig.h"
//#include "ftoledConfig.h"

unsigned long alarmStart = 0UL;
boolean soundAlarm = false;
boolean alarmSounding = false;
unsigned long ALARM_DURATION = 5000UL;


#endif  /* WIFLYMQTTMONITOR_CONFIG_H_ */

