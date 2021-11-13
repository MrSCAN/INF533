// Chinonso Stanislaus Ngwu, Changjie Wang, Hadi Rayan Al-Sandid
// INF533 - "Now you I2C me"


// Both master and slave communicate through I2C.
// Slave A and B have adresses 10 and 12 respectively.

// The master has four traffic light states corresponding to different
// traffic light configurations for Slave A and B.
// [1:<RED,GREEN>; 2:<RED-YELLOW,YELLOW>; 3:<GREEN,RED>; 4:<YELLOW,RED-YELLOW>]

// The master/slaves perform multiple operations to maintain this cycle without desync
// The master informs all slaves before each incoming operation by transmitting an 'operation code'
// 'm' : master sends state data to all slaves, 'l' : master requests state data from all slaves,
// 'k' : master requests button state from all slaves


#define red 2
#define yellow 3
#define green 4
#define BUTTON 6


#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  Wire.begin(12);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

boolean changeState = false;
boolean greenCross = false;
char state = '3';
char inst = ' ';
boolean offSwitchEnabled = true;
boolean msgType = false;

void loop() {

  if (digitalRead(BUTTON) == LOW && offSwitchEnabled)
  {
    offSwitchEnabled = false;

    greenCross = true;

  }

  if (digitalRead(BUTTON) == HIGH)
  {
    offSwitchEnabled = true;
  }

  if (changeState)
  {

    changeState = false;
    switch (state) {
      case '1':
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        break;
      case '2':
        digitalWrite(red, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        break;
      case '3':
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
        break;
      case '4':
        digitalWrite(red, LOW);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        break;
    }
  }


  delay(100);

}

void receiveEvent(int numBytes)
{
  char tempChar = ' ';

  
  while (Wire.available()) { // slave may send less than requested
    tempChar = Wire.read();
    if(tempChar == '1' || tempChar == '2' || tempChar == '3' || tempChar == '4' )
    {
      state = tempChar; 
      Serial.println("State is " + String(state));       // print the character
      changeState = true;
    }
    else
    {
      inst = tempChar;
      Serial.println("NEW Instruction is " + String(inst));       // print the character
    }
        
  }

}

void requestEvent() {

  if (inst == 'l')
  {
    Wire.write(state);
  }
  else if (inst == 'k')
  {
    if (greenCross)
    {
      Wire.write('y');
      greenCross = false;
    }
    else
    {
      Wire.write('n');
    }

  }
}
// put your main code here, to run repeatedly:
