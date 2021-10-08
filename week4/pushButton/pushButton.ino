/* Author: Chinonso Stanislaus Ngwu
   Imitating an XOR Logic gate (With some Flip Flop Effect) with two push buttons A and B and an LED (Not exactly an XOR though)
   Truth Table
   A  B OUTPUT
   0  0 0
   0  1 !prevState
   1  0 !prevState
   1  1 prevState  (This state was modified to make it a little fun as we want the LED to remain in it's current state until a new input is received)
*/
byte a = 11; //Button A Pin
byte b = 10; //Button B Pin
byte led = 2; //LED Pin
byte currentState = 0;
byte aState = 0;
byte bState = 0;
int aa;
int bb;
void setup() {
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  aa = digitalRead(a);
  bb = digitalRead(b);
  if (aa == 0 && aState == 0) {
    currentState = !currentState;
    aState = 1;
  } else if ((bb == 0) && bState == 0) {
    currentState = !currentState;;
    bState = 1;
  }else if (aa == 1 && aState == 1) {
    aState = 0;
  }else if (bb == 1 && bState == 1) {
    bState = 0;
  }
  digitalWrite(led, currentState);

}
