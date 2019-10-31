int pwmPin = 11;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    analogWrite(pwmPin, 1);
    delay(5000);
    analogWrite(pwmPin, 254);
    delay(5000);

}
