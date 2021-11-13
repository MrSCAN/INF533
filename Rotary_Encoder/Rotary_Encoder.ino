byte red = 9;
byte green = 3;
byte blue = 6;

byte redButton = 7;
byte blueButton = 4;
byte greenButton = 5;
byte offButton = 2;

const int clkPin = 10; //the clk attach to pin2
const int dtPin = 11; //the dt attach to pin3
const int swPin = 12 ; //the number of the button

int clk = digitalRead(clkPin);
int dt  = digitalRead(dtPin);

byte redState = 0;
byte blueState = 0;
byte greenState = 0;
byte offState = 0;
byte encoderState = 0;

byte redValue = 0;
byte greenValue = 0;
byte blueValue = 0;

byte transitionState = 0;

byte systemState;

byte redCounter = 0;
byte greenCounter = 0;
byte blueCounter = 0;
byte offCounter = 0;
byte encoderCounter = 0;



void setup() {

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(offButton, INPUT_PULLUP);

  pinMode(swPin, INPUT_PULLUP);

  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);

  digitalWrite(red, 1);
  digitalWrite(blue, 1);
  digitalWrite(green, 1);

  Serial.begin(9600);

}

void loop() {
  redState = digitalRead(redButton);
  greenState = digitalRead(greenButton);
  blueState =  digitalRead(blueButton);
  offState =  digitalRead(offButton);
  encoderState = digitalRead(swPin);

  if (redState == 0 && redCounter == 0) {
    systemState = 1;
    redCounter = 1;
  } else if (redState == 1 && redCounter == 1) {
    redCounter = 0;
  }  else if (greenState == 0 && greenCounter == 0) {
    greenCounter = 1;
    systemState = 2;
  } else if (greenState == 1 && greenCounter == 1) {
    greenCounter = 0;
  }  else if (blueState == 0 && blueCounter == 0) {
    systemState = 3;
    blueCounter = 1;
  } else if (blueState == 1 && blueCounter == 1) {
    blueCounter = 0;
  } else if (offState == 0 && offCounter == 0) {
    offCounter = 1;
    systemState = 4;
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 255);
  } else if (offState == 1 && offCounter == 1) {
    offCounter = 0;
  } else if (encoderState == 0 && encoderCounter == 0) {
    systemState = 0;
    encoderCounter = 1;
  } else if (encoderState == 1 && encoderCounter == 1) {
    encoderCounter = 0;
  }

  int newCLK = digitalRead(clkPin);
  int newDT = digitalRead(dtPin);
  for (int i = 0; i < 1600; i++) asm volatile ("NOP");
  if ( (newCLK != clk) && newCLK == LOW ) {
    if ( dt == LOW) {
      if (systemState == 1 && redValue < 255) {
        redValue += 1;
        analogWrite(red, 255 - redValue);
      } else if (systemState == 2 && greenValue < 255) {
        greenValue += 1;
        analogWrite(green, 255 - greenValue);
      } else if (systemState == 3 && blueValue < 255) {
        blueValue += 1;
        analogWrite(blue, 255 - blueValue);
      }
      Serial.println((String)"Red: " + redValue + " Green: " + greenValue + " Blue: " + blueValue);
    } else {
      if (systemState == 1 && redValue > 0) {
        redValue -= 1;
        analogWrite(red, 255 - redValue);
      } else if (systemState == 2 && greenValue > 0) {
        greenValue -= 1;
        analogWrite(green, 255 - greenValue);
      } else if (systemState == 3 && blueValue > 0) {
        blueValue -= 1;
        analogWrite(blue, 255 - blueValue);
      }
      Serial.println((String)"Red: " + redValue + " Green: " + greenValue + " Blue: " + blueValue);
    }
  }
  clk = newCLK;
  dt = newDT;
}
