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

#include <Wire.h>
#define SLAVE_A 10
#define SLAVE_B 12

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

int stateMaster = 1;
char charSlaveA = ' ';
char charSlaveB = ' ';
int transCount = 0;

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Master state is " + String(stateMaster));

  Wire.beginTransmission(SLAVE_A);
  Wire.write('m');
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_B);
  Wire.write('m');
  Wire.endTransmission();

  switch (stateMaster)
  {
    case 1:
      Wire.beginTransmission(SLAVE_A);
      Wire.write('1');
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write('3');
      Wire.endTransmission();
      break;
    case 2:
      Wire.beginTransmission(SLAVE_A);
      Wire.write('2');
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write('4');
      Wire.endTransmission();
      break;

    case 3:
      Wire.beginTransmission(SLAVE_A);
      Wire.write('3');
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write('1');
      Wire.endTransmission();
      break;

    case 4:
      Wire.beginTransmission(SLAVE_A);
      Wire.write('4');
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write('2');
      Wire.endTransmission();
      break;
  }



  Wire.beginTransmission(SLAVE_A);
  Wire.write('l');
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_B);
  Wire.write('l');
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_A, 1);
  while (Wire.available()) {
    charSlaveA = (char)Wire.read();
  }

  Serial.println("CharSlave A is " + String(charSlaveA));

  Wire.requestFrom(SLAVE_B, 1);
  while (Wire.available()) {
    charSlaveB = (char)Wire.read();
  }

  Serial.println("CharSlave B is " + String(charSlaveB));

  switch (stateMaster)
  {
    case 1:
      if (charSlaveA == '1' && charSlaveB == '3')
      {
        stateMaster = 2;
        transCount = 0;
      }
      break;
    case 2:
      if (charSlaveA == '2' && charSlaveB == '4')
      {
        stateMaster = 3;
        transCount = 0;
      }
      break;

    case 3:
      if (charSlaveA == '3' && charSlaveB == '1')
      {
        stateMaster = 4;
        transCount = 0;
      }
      break;

    case 4:
      if (charSlaveA == '4' && charSlaveB == '2')
      {
        stateMaster = 1;
        transCount = 0;
      }
      break;
  }

  transCount += 1;

  if (transCount > 10)
  {
    Serial.println("Re-transmission limit Reached!");
    delay(1000);
    exit(0);
  }

  Wire.beginTransmission(SLAVE_A);
  Wire.write('k');
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_B);
  Wire.write('k');
  Wire.endTransmission();

  delay(1500);



  Wire.requestFrom(SLAVE_A, 1);
  while (Wire.available()) {
    charSlaveA = (char)Wire.read();
  }

  Serial.println("2nd CharSlave A is " + String(charSlaveA));

  Wire.requestFrom(SLAVE_B, 1);
  while (Wire.available()) {
    charSlaveB = (char)Wire.read();
  }

  Serial.println("2nd CharSlave B is " + String(charSlaveB));

  if (charSlaveA == 'y')
  {
    transCount = 0;
    stateMaster = 3;
  }
  else if (charSlaveB == 'y')
  {
    transCount = 0;
    stateMaster = 1;
  }



}
