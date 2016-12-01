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
#include "tsic.h"

extern "C" {
  #include <inttypes.h>
  #include "WConstants.h"  //all things wiring / arduino
  #include "WProgram.h"
}

#define TSIC_ON()			digitalWrite(TSCI_POWER_PIN, HIGH)	// Power up the TSIC-Sensor
#define TSIC_OFF()			digitalWrite(TSCI_POWER_PIN, LOW)	// Power down the TSIC-Sensor
#define TSIC_SIGNAL_HIGH	digitalRead(TSIC_SIGNAL_PIN)		//if TSIC_SIGNAL_PIN is high (=1)
#define TSIC_SIGNAL_LOW		!digitalRead(TSIC_SIGNAL_PIN)		//if TSIC_SIGNAL_PIN is low  (=0)

//Konstrucktor
tsic::tsic(int Pin_VCC, int Pin_Sig)
{
	_Pin_VCC = Pin_VCC;
	_Pin_Sig = Pin_Sig;
	#define TSCI_POWER_PIN		_Pin_VCC            // Where TSIC-Sensors VCC is connected
	#define TSIC_SIGNAL_PIN		_Pin_Sig            // Where TSIC-Sensors "Signal"-Pin is connected
	pinMode(TSCI_POWER_PIN, OUTPUT);				// sets the digital pin as output
    pinMode(TSIC_SIGNAL_PIN, INPUT);      			// sets the digital pin as input
}

uint8_t tsic::getTSicTemp (int *temp_value16) {
	temp_value1 = 0;
	temp_value2 = 0;
	celsius = 0.0;

  TSIC_ON();

  delayMicroseconds(60);		// wait for stabilization

  while (TSIC_SIGNAL_HIGH);		// wait until start bit starts
  while (TSIC_SIGNAL_LOW);		// wait, TStrobe

  // first data byte
  // read 8 data bits and 1 parity bit
  for (i = 0; i < 9; i++) {
    while (TSIC_SIGNAL_HIGH);		// wait for falling edge
    delayMicroseconds(60);
	if (TSIC_SIGNAL_HIGH)
        temp_value1 |= 1 << (8-i);	// get the bit
      else
		while (TSIC_SIGNAL_LOW);		// wait until line comes high again
  }

  // second byte
  while (TSIC_SIGNAL_HIGH);		// wait until start bit starts
  while (TSIC_SIGNAL_LOW);		// wait, TStrobe
  // read 8 data bits and 1 parity bit
  for (i = 0; i < 9; i++) {
   while (TSIC_SIGNAL_HIGH);               // wait for falling edge
   delayMicroseconds(60);
   if (TSIC_SIGNAL_HIGH)
        temp_value2 |= 1 << (8-i);          // get the bit
   else
        while (TSIC_SIGNAL_LOW);            // wait until line comes high again
  }

  TSIC_OFF();                               // switch TSic off

  // check parity for byte 1
  parity = 0;
  for (i = 0; i < 9; i++)
    if (temp_value1 & (1 << i))
        parity++;
  if (parity % 2)
		return 0;

  // check parity for byte 2
  parity = 0;
  for (i = 0; i < 9; i++)
    if (temp_value2 & (1 << i))
        parity++;
  if (parity % 2)
        return 0;
  temp_value1 >>= 1;                 // delete parity bit
  temp_value2 >>= 1;                 // delete parity bit
  temp_Temperature = (temp_value1 << 8) | temp_value2;

//   celsius = ( (float)temp_Temperature / 2047 * 200) - 50;	// conversion equation from TSic's data sheet
   celsius = ( (float)temp_Temperature / 2047 * 7000) - 1000;	// conversion equation from TSic's data sheet 506
   *temp_value16 = celsius;

  return 1;                       // parity is OK
}