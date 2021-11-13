int trigPin = 11;
int echoPin = 10;

int btnPin = 2;

int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;

int buzzerPin = 9;

long duration;
long distance;
int state = 0;
int prevState = 0;
bool triggerAlarm = false;
long currentMillis = 0;
long prevMillis = 0;
int buzzerState = 1;

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btnPin, INPUT_PULLUP);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  int btnState = digitalRead(btnPin);
  if (btnState == 0) {
    triggerAlarm = false;
    digitalWrite(buzzerPin, LOW);
  }

  Serial.println((String)"Distance: " + distance);


  if (distance > 30) {
    state = 5;
  } else if (distance > 25) {
    state = 4;
  } else if (distance > 20) {
    state = 3;
  } else if (distance > 15) {
    state = 2;
  } else if (distance < 10) {
    state = 1;
  }

  if (state != prevState) {
    prevState = state;
    if (state == 1) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      triggerAlarm = true;
    } else if (state == 2) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
    } else if (state == 3) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
    } else if (state == 4) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
    } else if (state == 5) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }
  }

  if (triggerAlarm) {
    currentMillis = millis();
    if (currentMillis - prevMillis > 100) {
      buzzerState = !buzzerState;
      prevMillis = currentMillis;
    digitalWrite(buzzerPin, buzzerState);
    }
  }

}
