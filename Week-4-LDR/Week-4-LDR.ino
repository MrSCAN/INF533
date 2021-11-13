int redThreshold = 600;
int blueThreshold = 100;

byte redLed = 12;
byte greenLed = 11;
byte blueLed = 10;
int bandWidth = 5;
int prevValue = 0;

int setThresholdValue;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);

}

void loop() {

  int ldrValue = analogRead(A2);
//  for(int i = 0; i<100; i++){
//    ldrValue += analogRead(A2);
//  }
//  ldrValue = ldrValue/100;


  int thresholdBtnValue = analogRead(A1);

  if (thresholdBtnValue >= 0 && thresholdBtnValue <= 100 && !(ldrValue <= blueThreshold + bandWidth)) {
    redThreshold = ldrValue;
  } else if (thresholdBtnValue >= 450 && thresholdBtnValue <= 550 && !(ldrValue >= redThreshold + bandWidth)) {
    blueThreshold = ldrValue;
  }


  if (ldrValue > redThreshold+bandWidth) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
  } else if (ldrValue < blueThreshold - bandWidth) {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH);
  } else if (ldrValue <= redThreshold && ldrValue >= blueThreshold) {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);
  }


  Serial.println((String)"RED Threshold: "+redThreshold +" GREEN Threshold: "+blueThreshold+" LDR Value: "+ldrValue+" Threshold Read: "+thresholdBtnValue);
}
