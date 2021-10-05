void setup() {
  for (int i = 7; i >= 2;) {
    pinMode(i, OUTPUT);
    i = i - 1;
  }
}

int delayTime = 300;
void loop() {
    //1
  for (int i = 7; i >= 3;) {
    digitalWrite(i, HIGH);
    i = i - 1;
    delay(delayTime);
  }

  //2
  for (int i = 3; i <= 7;) {
    digitalWrite(i, LOW);
    delay(delayTime);
    i = i + 1;
  }

  //3
  for (int i = 3; i <= 7;) {
    digitalWrite(i, HIGH);
    i = i + 1;
  }
  delay(delayTime);
  for (int i = 3; i <= 7;) {
    digitalWrite(i, LOW);
    i = i + 1;
  }
  delay(delayTime);


  //4
  for (int i = 7; i >= 3;) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
    delay(delayTime);
    i = i - 1;
  }

  //5
  for (int i = 4; i <= 7;) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
    delay(delayTime);
    i = i + 1;
  }
  
  if(delayTime == 300){
    delayTime = 200;
  }else {
    delayTime = 300;
  }  
}
