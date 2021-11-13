byte red = 11;
byte green = 10;
byte blue = 9;

byte redButton = 4;
byte blueButton = 6;
byte greenButton = 5;
byte offButton = 7;

byte redState = 0;
byte blueState = 0;
byte greenState = 0;
byte offState = 0;

byte redValue = 0;
byte greenValue = 0;
byte blueValue = 0;

byte transitionState = 0;

byte systemState;

byte redCounter = 0;
byte greenCounter = 0;
byte blueCounter = 0;
byte offCounter = 0;

byte prevState = 0;

byte delayValue = 25;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(offButton, INPUT_PULLUP);

  digitalWrite(red, 1);
  digitalWrite(blue, 1);
  digitalWrite(green, 1);

//  Serial.begin(9600);

}

void loop() {
  redState = digitalRead(redButton);
  greenState = digitalRead(greenButton);
  blueState =  digitalRead(blueButton);
  offState =  digitalRead(offButton);
  if (redState == 0 && redCounter == 0) {
    systemState = 1;
    redCounter = 1;
    redValue = prevState;
    blueValue = 0;
    greenValue = 0;
    analogWrite(green, 255);
    analogWrite(blue, 255);
  } else if (redState == 1 && redCounter == 1) {
    redCounter = 0;
  }  else if (greenState == 0 && greenCounter == 0) {
    greenCounter = 1;
    systemState = 2;
    greenValue = prevState;
    redValue = 0;
    blueValue = 0;
    analogWrite(red, 255);
    analogWrite(blue, 255);
  } else if (greenState == 1 && greenCounter == 1) {
    greenCounter = 0;
  }  else if (blueState == 0 && blueCounter == 0) {
    systemState = 3;
    blueCounter = 1;
    blueValue = prevState;
    redValue = 0;
    greenValue = 0;
    analogWrite(green, 255);
    analogWrite(red, 255);
  } else if (blueState == 1 && blueCounter == 1) {
    blueCounter = 0;
  } else if (offState == 0 && offCounter == 0) {
    offCounter = 1;
    systemState = 4;
    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 255);
  } else if (offState == 1 && offCounter == 1) {
    offCounter = 0;
  }


  if (systemState == 1 && transitionState == 0 && redValue <= 255) {
    if (redValue == 255) {
      transitionState = 1;
    } else {
      redValue += 1;
      prevState = redValue;
      greenValue = 0;
      blueValue = 0;
      analogWrite(red, 255 - redValue);
    }
  } else if (systemState == 1 && transitionState == 1 && redValue >= 0) {

    if (redValue == 0) {
      transitionState = 0;
    } else {
      redValue -= 1;
      prevState = redValue;
      greenValue = 0;
      blueValue = 0;
      analogWrite(red, 255 - redValue);
    }
  }


  else if (systemState == 2 && transitionState == 0 && greenValue <= 255) {

    if (greenValue == 255) {
      transitionState = 1;
    } else {
      greenValue += 1;
      prevState = greenValue;
      redValue = 0;
      blueValue = 0;
      analogWrite(green, 255 - greenValue);
    }
  } else if (systemState == 2 && transitionState == 1 && greenValue >= 0) {

    if (greenValue == 0) {
      transitionState = 0;
    } else {
      greenValue -= 1;
      prevState = greenValue;
      redValue = 0;
      blueValue = 0;
      analogWrite(green, 255 - greenValue);
    }
  } else if (systemState == 3 && transitionState == 0 && blueValue <= 255) {

    if (blueValue == 255) {
      transitionState = 1;
    } else {
      blueValue += 1;
      prevState = blueValue;
      analogWrite(blue, 255 - blueValue);
    }
  } else if (systemState == 3 && transitionState == 1 && blueValue >= 0) {

    if (blueValue == 0) {
      transitionState = 0;
    } else {
      blueValue -= 1;
      prevState = blueValue;
      analogWrite(blue, 255 - blueValue);
    }
  }
  delay(delayValue);
//  Serial.println((String)"Red: "+redValue+" Green: "+greenValue+" Blue: "+blueValue);
}
