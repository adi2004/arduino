#include <tsic.h>
/*Don't use Digital Pin 13 for Tsic-Sensor, because it is intern connected with a LED*/

int error1, error2;  //1 = OK, 0 = parity error    return value of getTSicTemp()
int temperatur1, temperatur2;  // "return" of temperture
float temp1, temp2;

tsic Sensor1(8, 9);  //firstValue = VCC-Pin, secondValue = Signal-Pin
int ground1 = 10;

tsic Sensor2(5, 6);
int ground2 = 7;

void setup(){
  Serial.begin (9600);
  pinMode(ground1, OUTPUT);
  digitalWrite(ground1, LOW);
  pinMode(ground2, OUTPUT);
  digitalWrite(ground2, LOW);
}
void loop(){ 
  error1 = Sensor1.getTSicTemp(&temperatur1);  //turn the TSIC-Sensor ON -> messure -> OFF
  temp1=temperatur1/100.0;
  error2 = Sensor2.getTSicTemp(&temperatur2);  //turn the TSIC-Sensor ON -> messure -> OFF
  temp2=temperatur2/100.0;
   
  Serial.print("Temperatur1: ");
  Serial.print(temp1);
  Serial.print(" Temperatur2: ");
  Serial.print(temp2);
  if (error1 == 1 && error2 == 1)
  {
    Serial.println(" Parity OK!");
  } else
  {
    Serial.println(" Read FAIL!");
  }
  delay(100);
}

