/**
 *  test ard-tsiclib by reading the temperature every second
 *  and output the measured data to the serial port
 */

#include "TSIC.h"       // include the library

TSIC Sensor1( 3,  4, TSIC_50x);    // external powering of 50x-Sensor NO_VCC_PIN
TSIC Sensor2( 6,  7, TSIC_50x);    // external powering of 50x-Sensor NO_VCC_PIN
TSIC Sensor3( 9, 10, TSIC_50x);    // external powering of 50x-Sensor NO_VCC_PIN
TSIC Sensor4(12, 13, TSIC_50x);    // external powering of 50x-Sensor NO_VCC_PIN
TSIC Sensor5(24, 22, TSIC_50x);    // external powering of 50x-Sensor NO_VCC_PIN
// instantiate the library, representing the sensor
//TSIC Sensor1(4, 2);    // Signalpin, VCCpin, Sensor Type
//TSIC Sensor3(1);    // only Signalpin, VCCpin unused by default
//TSIC Sensor2(6, 7, TSIC_30x);    // Signalpin, VCCpin, Sensor TypeTSIC Sensor2(5, 2, TSIC_50x);  // Signalpin, VCCpin, Sensor Type NOTE: we can use the same VCCpin to power several sensors

uint16_t temperature = 0;
float Temperatur_C = 0;

void setup() {
    Serial.begin(9600); // set up the serial port
    
    setGND(2);
    setGND(5);
    setGND(8);
    setGND(11);
    setGND(26);
}

void setGND(int i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
}

int cycle = 0;
char dataString[50] = {0};
void loop() {
    /*Serial.print("Starting cycle ");
    Serial.print(cycle++);
    Serial.println(" ...");
    */
    sprintf(dataString,"%02X",getValue(Sensor1));
    Serial.println(dataString);
    delay(1000);
    /*
    displaySensor(Sensor1, 1);
    displaySensor(Sensor2, 2);
    displaySensor(Sensor3, 3);
    displaySensor(Sensor4, 4);
    displaySensor(Sensor5, 5);
    Serial.println(" ");
    delay(60000);    // wait 1 seconds*/
}

void displaySensor(TSIC sensor, int i) {
    if (sensor.getTemperature(&temperature)) {
        //Serial.print("uint_16: ");
        //Serial.println(temperature);
        Temperatur_C = sensor.calc_Celsius(&temperature);
        //Serial.print("Temperature for ");
        Serial.print(i);
        Serial.print(":");
        Serial.print(Temperatur_C);
        Serial.print(" ");
        //Serial.println(" °C");
    }
}

int getValue(TSIC sensor) {
    if (sensor.getTemperature(&temperature)) {
        return (int) sensor.calc_Celsius(&temperature)*1000;
    }
}

