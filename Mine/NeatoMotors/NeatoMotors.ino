/*
 * Neato Test :
 *       1. Power Up
 *       2. Wait for 5 secs
 *       3. Move F for 3 secs
 *       4. Stop for 1.5 secs
 *       5. Turn Right for 1.5 secs
 *       6. Stop for 1.5 secs
 *       6. Move B for 3 secs
 *       7. Stop for 1.5 secs
 *       8. Turn Left for 1.5 secs
 *       9. Stop for 1.5 secs
 *       10. Squiggle F and B 
 *       11. Squiggle while turning
 *   
 */

//Wheel 1 - Right

int W1FRel = 2; // Forward Relay
int W1FFet = 3; // Forward Speed Control - MosFET
int W1BRel = 4; // Backwards Relay
int W1BFet = 5; // Backwards Speed Control - MosFET

//Wheel 2 - Left
  
int W2FRel = 8; // Forward Relay
int W2FFet = 9; // Forward Speed Control - MosFET
int W2BRel = 10; // Backwards Relay
int W2BFet = 11; // Backwards Speed Control - MosFET

void Forward(int Sp, int Time) {
  digitalWrite(W1FRel, HIGH);
  digitalWrite(W2FRel, HIGH);
  delay(20);
  analogWrite(W1BFet, Sp);
  analogWrite(W2BFet, Sp);
  int T = Time * 1000;
  delay(T);
  analogWrite(W1FFet, 0);
  analogWrite(W2FFet, 0);
  delay(20);
  digitalWrite(W1FRel, LOW);
  digitalWrite(W2FRel, LOW);
  delay(20);
}

void Backward(int Sp, int Time) {
  digitalWrite(W1BRel, HIGH);
  digitalWrite(W2BRel, HIGH);
  delay(20);
  analogWrite(W1BFet, Sp);
  analogWrite(W2BFet, Sp);
  int T = Time * 1000;
  delay(T);
  analogWrite(W1BFet, 0);
  analogWrite(W2BFet, 0);
  delay(20);
  digitalWrite(W1BRel, LOW);
  digitalWrite(W2BRel, LOW);
  delay(20);
}

void TurnR(int Sp, int Time) {
  digitalWrite(W1BRel, HIGH);
  digitalWrite(W2FRel, HIGH);
  delay(20);
  analogWrite(W1BFet, Sp);
  analogWrite(W2FFet, Sp);
  int T = Time * 1000;
  delay(T);
  analogWrite(W1BFet, 0);
  analogWrite(W2FFet, 0);
  delay(20);
  digitalWrite(W1BRel, LOW);
  digitalWrite(W2FRel, LOW);
  delay(20);
}

void TurnL(int Sp, int Time) {
  digitalWrite(W1FRel, HIGH);
  digitalWrite(W2BRel, HIGH);
  delay(20);
  analogWrite(W1FFet, Sp);
  analogWrite(W2BFet, Sp);
  int T = Time * 1000;
  delay(T);
  analogWrite(W1FFet, 0);
  analogWrite(W2BFet, 0);
  delay(20);
  digitalWrite(W1FRel, LOW);
  digitalWrite(W2BRel, LOW);
  delay(20);
}
void Wait(int secs) {
  int W = secs *1000;
  delay(W);
}


void setup() {

  pinMode(W1FRel, OUTPUT);
  pinMode(W1FFet, OUTPUT);
  pinMode(W1BRel, OUTPUT);
  pinMode(W1BFet, OUTPUT);
  pinMode(W2FRel, OUTPUT);
  pinMode(W2FFet, OUTPUT);
  pinMode(W2BRel, OUTPUT);
  pinMode(W2BFet, OUTPUT);
  
}

void loop() {

  Wait(5);
  Forward(255, 3);
  Wait(1.5);
  TurnR(255, 1.5);
  Wait(1.5);
  TurnL(255, 1.5);
  Wait(1.5);
  Backward(255, 3);

}
