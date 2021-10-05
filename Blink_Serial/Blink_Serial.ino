void setup() {
  Serial.begin(9600);
  for (int i = 7; i >= 3;) {
    pinMode(i, OUTPUT);
    i = i - 1;
  }
  for (int i = 1; i <= 5; i++) {
    Serial.println((String)"Enter " + i + " for pattern " + i);
  }
}

int delayTime = 500;
int pattern = 0;
int newPattern = 0;

bool checkSerial() {
  if (Serial.available() > 0) {
    newPattern = Serial.parseInt();
    if ((newPattern != pattern)) {
      if ((newPattern > 0)) {
        pattern = newPattern;
        newPattern = 0;
        Serial.println((String)"Pattern " + pattern + " running");
        return true;
      }
    }
  }
}

void loop() {
  checkSerial();
  if (pattern == 1) {
    patternOne();
  } else if (pattern == 2) {
    patternTwo();
  } else if (pattern == 3) {
    patternThree();
  } else if (pattern == 4) {
    patternFour();
  } else if (pattern == 5) {
    patternFive();
  } else {
    Serial.println("Default Pattern running");
    defaultPattern();
  }
}


void patternOne() {
  //1
  for (int i = 7; i >= 3;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    i = i - 1;
    delay(delayTime);
  }
  pattern = 0;
}

void patternTwo() {
  //2
  for (int i = 3; i <= 7;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    delay(delayTime);
    i = i + 1;
  }
  pattern = 0;
}

void patternThree() {
  //3
  for (int i = 3; i <= 7;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    i = i + 1;
  }
  //3
  for (int i = 7; i <= 3;) {
    if (checkSerial()) break;
    digitalWrite(i, LOW);
    i = i - 1;
  }
  pattern = 0;
}

void patternFour() {
  for (int i = 3; i <= 7;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    i = i + 1;
  }
  delay(delayTime);
  pattern = 0;

}

void patternFive() {
  //4
  for (int i = 7; i >= 3;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    i = i - 1;
    delay(delayTime);
  }
  for (int i = 7; i >= 3;) {
    if (checkSerial()) break;
    digitalWrite(i, LOW);
    i = i - 1;
    delay(delayTime);
  }
  pattern = 0;
}

void defaultPattern() {
  for (int i = 3; i <= 7;) {
    if (checkSerial()) break;
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
    delay(delayTime);
    i = i + 1;
  }
}
