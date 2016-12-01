#include <tsic.h>
/*Don't use Digital Pin 13 for Tsic-Sensor, because it is intern connected with a LED*/

int error;  //1 = OK, 0 = parity error    return value of getTSicTemp()
int temperatur;  // "return" of temperature in degrees Celsius * 100
float temp; // temperature in degrees Celsius

tsic Sensor1(3, 2);  //firstValue = VCC-Pin, secondValue = Signal-Pin

void setup(){
  Serial.begin (9600);

}
void loop(){ 
  error = Sensor1.getTSicTemp(&temperatur);  //turn the TSIC-Sensor ON -> messure -> OFF
  temp=temperatur/100.0;
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.println(" GradCelsius");
  Serial.print("Status: ");
  Serial.println(error);
  delay(1000);
}
