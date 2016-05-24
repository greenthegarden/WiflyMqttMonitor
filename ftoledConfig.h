#ifndef WIFLYMQTTMONITOR_FTOLED_CONFIG_H_
#define WIFLYMQTTMONITOR_FTOLED_CONFIG_H_


#include <FTOLED.h>

const byte pin_cs = 7;
const byte pin_dc = 2;
const byte pin_reset = 3;

OLED oled(pin_cs, pin_dc, pin_reset);


#endif  /* WIFLYMQTTMONITOR_FTOLED_CONFIG_H_ */

