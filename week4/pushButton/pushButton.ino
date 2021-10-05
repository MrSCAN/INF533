/* Author: Chinonso Stanislaus Ngwu
 * Imitating an XOR Logic gate (With some Flip Flop Effect) with two push buttons A and B and an LED (Not exactly an XOR though)
 * Truth Table
 * A  B OUTPUT
 * 0  0 0
 * 0  1 1
 * 1  0 1
 * 1  1 prevState  (This state was modified to make it a little fun as we want the LED to remain in it's current state until a new input is received) 
 */
int a = 11; //Button A Pin
int b = 10; //Button B Pin
int led = 2; //LED Pin
int prevState = 0;
int currentState = 0;
void setup() {
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  }

void loop() {
  if(digitalRead(a) == 0 && digitalRead(b) == 0){
    currentState = 0;
    prevState = currentState;
  }else if((digitalRead(a) == 0 && digitalRead(b) == 1) || (digitalRead(a) == 1 && digitalRead(b) == 0)){
    currentState = 1;
    prevState = currentState;
  }else{
    currentState = prevState; //remain in the previous state until a new input is received
  }
  digitalWrite(led, currentState);
  delay(100); 
}
