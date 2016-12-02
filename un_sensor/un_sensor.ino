// This is only to work with one sensor

int pin_vcc = 14;
int pin_signal = 15;
int pin_ground = 16;

void setup() {
  Serial.begin(9600);
  Serial.println("Now we start!");
  pinMode(pin_vcc, OUTPUT);
  digitalWrite(pin_vcc, HIGH);
  pinMode(pin_signal, INPUT);
  pinMode(pin_ground, OUTPUT);
  digitalWrite(pin_vcc, LOW);
}

void loop() {
  int state = digitalRead(pin_singal);
  Serial.print();
}
