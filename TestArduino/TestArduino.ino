/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int led = 0;
int ground = 10;
int signal = 9;
int vPlus = 8;
int savedState;
int counter = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  pinMode(ground, OUTPUT);
  pinMode(signal, INPUT);
  pinMode(vPlus, OUTPUT);
  digitalWrite(ground, LOW);
  digitalWrite(vPlus, HIGH);
  savedState = digitalRead(signal);
  Serial.print("Current state is: ");
  Serial.println(savedState);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int signalState = digitalRead(signal);
  // print out the state of the button:
  Serial.print(signalState);
  if (counter++ > 160)
  {
    Serial.println();
    counter = 0;
  }
  /*if (savedState != signalState)
  {
    Serial.print("State changed to: ");
    Serial.println(signalState);
    savedState = signalState;
  }*/
  //delay(1);        // delay in between reads for stability
}



