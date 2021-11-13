#include <Wire.h>

const int red = 2;
const int yellow = 3;
const int green = 4;

int btnValue;
byte state = 0;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  Wire.begin(10);
  /*Event Handlers*/
  Wire.onReceive(DataReceive);
  Wire.onRequest(DataRequest);
}

void loop() {
}


void DataReceive(int numBytes)
{
  byte inp;
  while (Wire.available())
  {
    inp = Wire.read();
    Serial.println(inp);
    if (inp == 1) {
      state = 1;
    } else if (inp == 2) {
      state = 2;
    } else if (inp == 3) {
      state = 3;
    } else if (inp == 4) {
      state = 4;
    }
  }

  switch (state) {
    case 1:
      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      break;
    case 2:
      digitalWrite(red, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
      break;
    case 3:
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
      break;
    case 4:
      digitalWrite(red, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
      break;
  }
}

void DataRequest()
{
  Wire.write(state);
}
