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
byte slaveA_sent = 0;
byte slaveB_sent = 0;
int delayTime = 3000;
int transmissionCount = 0;
int maxTransCount = 100;
int runCode = 0;

void loop() {
  if (runCode == 0) {
    switch (stateMaster)
    {
      case 1:
        slaveA_sent = 1;
        slaveB_sent = 3;
        break;
      case 2:
        slaveA_sent = 2;
        slaveB_sent = 4;
        break;

      case 3:
        slaveA_sent = 3;
        slaveB_sent = 1;
        break;

      case 4:
        slaveA_sent = 4;
        slaveB_sent = 2;
        break;
    }
    Wire.beginTransmission(SLAVE_A);
    Wire.write(slaveA_sent);
    Wire.endTransmission();

    Wire.beginTransmission(SLAVE_B);
    Wire.write(slaveB_sent);
    Wire.endTransmission();

    delay(50);

    transmissionCount += 1;

    Wire.requestFrom(SLAVE_A, 1);
    if (Wire.available()) {
      charSlaveA = Wire.read();
    }

    Wire.requestFrom(SLAVE_B, 1);
    if (Wire.available()) {
      charSlaveB = Wire.read();
    }

    if (slaveA_sent == charSlaveA && slaveB_sent == charSlaveB) {
      transmissionCount = 0;
      if (stateMaster < 4) {
        stateMaster += 1;
      }
      else {
        stateMaster = 1;
      }
      delay(delayTime);
    }

    Wire.beginTransmission(SLAVE_A);
    Wire.write(5);
    Wire.endTransmission();

    Wire.beginTransmission(SLAVE_B);
    Wire.write(5);
    Wire.endTransmission();

    delay(50);
    Wire.requestFrom(SLAVE_A, 1);
    if (Wire.available()) {
      charSlaveA = Wire.read();
    }

    Wire.requestFrom(SLAVE_B, 1);
    if (Wire.available()) {
      charSlaveB = Wire.read();
    }
    
    if (charSlaveA == 8) {
      stateMaster = 3;
    } else if (charSlaveB == 8) {
      stateMaster = 1;
    }

    if (transmissionCount > maxTransCount) {
      Serial.println("System Error...");
      runCode = 1;
    }
  }
}

void DataReceive(int numBytes)
{
  byte inp;
  if (Wire.available())
  {
    stateMaster = inp;
  }
}
