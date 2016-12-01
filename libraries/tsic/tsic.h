/*
  Library for TSIC digital Temperature Sensor Type 206/306 and may more.
  using ZACwire™ Communication Protocol for the TSic™
  Manufatorer:		IST AG, Hygrosens, ZMD
  Original Code:	http://www.mikrocontroller.net/topic/82087
  rewritten by:		Rolf W.
  Date:				2010.03.06
  adapted for TSic506 by: Nick van de Giesen, 25.9.2010  
  Temperature-sensor uses 2 Pins, one for VCC and the second for Signal (= ZACwire Protocol).
  With call of the Function ".....getTSicTemp();" the Senor will get power measure and will be turned OFF.
  In that case it uses only energy while measuring. There is another method with Interrupts, measuring
  at an constant rate, which is not implemented jet.
*/
#ifndef tsic_H
#define tsic_H
#include <inttypes.h>
#include "Arduino.h"

class tsic {
public:
	tsic(int Pin_VCC, int Pin_Sig);	//Constructor
	uint8_t getTSicTemp (int *temp_value16);
private:
	int _Pin_VCC;
	int _Pin_Sig;
	uint16_t temp_Temperature;
	uint8_t parity;
	uint8_t i;
	uint16_t temp_value1;
	uint16_t temp_value2;
	int celsius;
};
#endif
