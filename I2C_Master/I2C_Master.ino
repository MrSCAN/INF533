#include <Wire.h>
#define SLAVE_A 10
#define SLAVE_B 12

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

int stateMaster = 1;
byte charSlaveA = 0;
byte charSlaveB = 0;
int delayTime = 3000;
int transmissionCount = 0;
int maxTransCount = 10;
int runCode = 0;

void loop() {
  if(runCode == 0){
  switch (stateMaster)
  {
    case 1:
      Wire.beginTransmission(SLAVE_A);
      Wire.write(1);
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write(3);
      Wire.endTransmission();
      break;
    case 2:
      Wire.beginTransmission(SLAVE_A);
      Wire.write(2);
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write(4);
      Wire.endTransmission();
      break;

    case 3:
      Wire.beginTransmission(SLAVE_A);
      Wire.write(3);
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write(1);
      Wire.endTransmission();
      break;

    case 4:
      Wire.beginTransmission(SLAVE_A);
      Wire.write(4);
      Wire.endTransmission();

      Wire.beginTransmission(SLAVE_B);
      Wire.write(2);
      Wire.endTransmission();
      break;
  }
  transmissionCount += 1;

  Wire.requestFrom(SLAVE_A, 1);
  if (Wire.available()) {
    charSlaveA = Wire.read();
  }

    Wire.requestFrom(SLAVE_B, 1);
   if (Wire.available()) {
      charSlaveB = Wire.read();
    }

    switch (stateMaster)
    {
      case 1:
        if (charSlaveA == 1 && charSlaveB == 3)
        {
          stateMaster = 2;
          transmissionCount = 0;
          delay(delayTime);
        }
        break;
      case 2:
        if (charSlaveA == 2 && charSlaveB == 4)
        {
          stateMaster = 3;
          transmissionCount = 0;
          delay(delayTime);
        }
        break;
  
      case 3:
        if (charSlaveA == 3 && charSlaveB == 1)
        {
          stateMaster = 4;
          transmissionCount = 0;
          delay(delayTime);
        }
        break;
  
      case 4:
        if (charSlaveA == 4 && charSlaveB == 2)
        {
          stateMaster = 1;
          transmissionCount = 0;
          delay(delayTime);
        }
        break;
    }
    if(transmissionCount > maxTransCount){
      Serial.println("System Error...");
      runCode = 1;
    }
  }
}
