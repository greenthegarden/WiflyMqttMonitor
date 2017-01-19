#ifndef WIFLYMQTTMONITOR_CONFIG_H_
#define WIFLYMQTTMONITOR_CONFIG_H_


#include "debug.h"


const byte BUFFER_SIZE             = 60;
char progBuffer[BUFFER_SIZE];
char messBuffer[BUFFER_SIZE];

// Macros
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

const int BAUD_RATE                = 9600;


#include <MemoryFree.h>

#include "watchdogConfig.h"

#include "wiFlyConfig.h"
#include "mqttConfig.h"

#include "oledShieldConfig.h"
//#include "ftoledConfig.h"


unsigned long alarmStart           = 0UL;
boolean soundAlarm                 = false;
boolean alarmSounding              = false;
const unsigned long ALARM_DURATION = 5000UL;


#endif  /* WIFLYMQTTMONITOR_CONFIG_H_ */
