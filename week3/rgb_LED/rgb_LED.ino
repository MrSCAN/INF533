// Define Pins
#define RED 3
#define GREEN 5
#define BLUE 6
#define delayTime 10 // fading time between colours
#define DEBUG 0

// define variables
int redValue = 255;
int greenValue = 0;
int blueValue = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  if (DEBUG) {
    Serial.begin(9600);
  }
}




void loop() {

  if (blueValue < 255 && greenValue == 0 && redValue > 0) {
    blueValue += 1;
    redValue -= 1;
  }

  else if (redValue == 0 && greenValue < 255 && blueValue > 0) {
    blueValue -= 1;
    greenValue += 1;
  }

  else if (greenValue > 0 && blueValue == 0 && redValue < 255) {
    redValue += 1;
    greenValue -= 1;
  }

  analogWrite(RED, 255 - redValue);
  analogWrite(GREEN, 255 - greenValue);
  analogWrite(BLUE, 255 - blueValue);

  debugCode();
  if (!DEBUG) {
    delay(delayTime);
  }

}

void debugCode() {
  if (DEBUG == 1) {
    Serial.println((String)"RED: " + redValue + " GREEN: " + greenValue + " BLUE: " + blueValue);
  }
}
