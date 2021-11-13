#include <Wire.h>

const int red = 2;
const int yellow = 3;
const int green = 4;

const int btnPin = 6;

int btnValue;
byte state = 0;
byte state_pre = 0;
int readCount = 0;
int payL = 0;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(btnPin, INPUT_PULLUP);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  Wire.begin(10);
  /*Event Handlers*/
  Wire.onReceive(DataReceive);
  Wire.onRequest(DataRequest);
}
int btnStatus = 7;

void loop() {

  int btnState = digitalRead(btnPin);
  if (btnState == LOW && readCount == 0) {
    btnStatus = 8;
    readCount = 1;
  } else if (btnState == HIGH) {
    readCount = 0;
    btnStatus = 7;
  }



  if (state != state_pre) {
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
    state_pre = state;
  }
}


void DataReceive(int numBytes)
{
  byte inp;
  while (Wire.available())
  {
    inp = Wire.read();
    if (inp == 1) {
      state = 1;
      payL = 1;
    } else if (inp == 2) {
      state = 2;
      payL = 2;
    } else if (inp == 3) {
      state = 3;
      payL = 3;
    } else if (inp == 4) {
      state = 4;
      payL = 4;
    }else if(inp = 5){
      payL = btnStatus;
    }
  }
}

void DataRequest()
{
  Wire.write(payL);
}
