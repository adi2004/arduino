#include "tsic.h"
/*Don't use Digital Pin 13 for Tsic-Sensor, because it is intern connected with a LED*/

tsic Sensor1(11, 12, 13);
tsic Sensor2( 8,  9, 10);  //firstValue = VCC-Pin, secondValue = Signal-Pin
tsic Sensor3( 5,  6,  7);
tsic Sensor4( 2,  3,  4);
tsic Sensor5(20, 22, 24);

void setup(){
  Serial.begin (9600);
  Serial.println("Now it begins: ");
}
void loop(){
  unsigned long start, stopt;
//  Serial.println("-- starting to read --");
  start = micros();
  Sensor1.getTSicTempNoPower();
  Sensor2.getTSicTempNoPower();
  Sensor3.getTSicTempNoPower();
  Sensor4.getTSicTempNoPower();
  Sensor5.getTSicTempNoPower();
  stopt = micros();
//  Serial.println("-- read ended --");
  Serial.print("Temps = ( ");
  Serial.print(Sensor1.temperature);
  Serial.print(", ");
  Serial.print(Sensor2.temperature);
  Serial.print(", ");
  Serial.print(Sensor3.temperature);
  Serial.print(", ");
  Serial.print(Sensor4.temperature);
  Serial.print(", ");
  Serial.print(Sensor5.temperature);
  Serial.print(" ); t = ");
  Serial.print(stopt-start);
  Serial.print(" us; ");
  Serial.print("time to decode = ( ");
  Serial.print(Sensor1.measureTime);
  Serial.print(", ");
  Serial.print(Sensor2.measureTime);
  Serial.print(", ");
  Serial.print(Sensor3.measureTime);
  Serial.print(", ");
  Serial.print(Sensor4.measureTime);
  Serial.print(", ");
  Serial.print(Sensor5.measureTime);
  Serial.print(" ) us ");
  
  Serial.println();
}

