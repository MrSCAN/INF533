// Define Pins
#define RED 3
#define GREEN 5
#define BLUE 6
#define delayTime 10 // fading time between colours
#define DEBUG 1

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

// define variables
int redValue;
int greenValue;
int blueValue;


//Smooth transition for rainbow colors

void loop() {
  redValue = 255; // Turn on red.
  greenValue = 0;
  blueValue = 0;
  analogWrite(RED, 255 - redValue);
  analogWrite(GREEN, 255 - greenValue);
  analogWrite(BLUE, 255 - blueValue);
  delay(1000);

  for (int i = 0; i < 127; i += 1) { // fade out red, bring Orange  (Red 255, Green 127, Blue 0)
    greenValue += 1;
    analogWrite(RED, 255 - redValue);
    analogWrite(GREEN, 255 - greenValue);
    delay(delayTime);
  }
  debugCode();
  redValue = 255;
  greenValue = 127;
  blueValue = 0;


  for (int i = 127; i < 255; i += 1) { // fade out Orange, bring Yellow  (Red 255, Green 255, Blue 0)
    greenValue += 1;
    analogWrite(GREEN, 255 - greenValue);
    delay(delayTime);
  }
  debugCode();

  redValue = 255;
  greenValue = 255;
  blueValue = 0;


  for (int i = 0; i < 255; i += 1) { // fade out Orange, bring Green  (Red 0, Green 255, Blue 0)
    redValue -= 1;
    analogWrite(GREEN, 255 - greenValue);
    delay(delayTime);
  }
  debugCode();
  redValue = 0;
  greenValue = 255;
  blueValue = 0;


  for (int i = 0; i < 255; i += 1) { // fade out green bring blue (Red 0, Green 0, Blue 255)
    greenValue -= 1;
    blueValue += 1;
    analogWrite(GREEN, 255 - greenValue);
    analogWrite(BLUE, 255 - blueValue);
    delay(delayTime);
  }
  debugCode();
  redValue = 0;
  greenValue = 0;
  blueValue = 255;


  for (int i = 0; i < 75; i += 1) { // fades out blue bring Indigo (Red 75, Green 0, Blue 130)
    redValue += 1;
    blueValue -= 2;  //Approximated value of 150 for Blue
    blueValue = (int)(blueValue * 0.87);  //Add correction factor 130/150 = 0.87
    analogWrite(RED, 255 - redValue);
    analogWrite(BLUE, 255 - blueValue);
    delay(delayTime);
  }
  debugCode();
  redValue = 75;
  greenValue = 0;
  blueValue = 130;


  for (int i = 75; i < 148; i += 1) { // fades out Indigo bring Violet (Red 148, Green 0, Blue 211)
    redValue += 1;
    blueValue += 1;  //Approximated value of 203 for Blue
    analogWrite(RED, 255 - redValue);
    analogWrite(BLUE, 255 - blueValue);
    delay(delayTime);
  }
  debugCode();
  redValue = 148;
  greenValue = 0;
  blueValue = 211;


  for (int i = 148; i < 255; i += 1) { // fades out Indigo bring Violet (Red 148, Green 0, Blue 211)
    redValue += 1;
    blueValue -= 7;  
    if(blueValue < 0){
      blueValue == 0;
    }
    analogWrite(RED, 255 - redValue);
    analogWrite(BLUE, 255 - blueValue);
    delay(delayTime);
  }
  debugCode();

}

void debugCode(){
  if(DEBUG == 1){
    Serial.println((String)"RED: " + redValue + " GREEN: " + greenValue + "BLUE: " + blueValue);
  }
}
