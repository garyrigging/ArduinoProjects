const int  buttonPin = 9; //    Selector button read pin
const int  timePotPin = 8; //   Time pot OUT signal pin
const int  timeRead = A0; //    Time pot read pin
const int  loadRelay = A1; //    Load relay signal pin

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//---------------------------------------------

const int numReadings = 30;     //smoothing
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int analogMap;                  // the analogMapping of the time selection pot

//--------------------------------------------

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // LCD - Rs, E, Db4, Db5, Db6, Db7

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  pinMode(timeRead, INPUT);
  pinMode(timePotPin, OUTPUT);
  pinMode(loadRelay, OUTPUT);
  
  digitalWrite(loadRelay,LOW);
  
for (int thisReading = 0; thisReading < numReadings; thisReading++) { //Smoothing purpose
    readings[thisReading] = 0;
  }

  lcd.begin(16,2);
  digitalWrite(buttonPin,LOW);
  delay(50);
  lcd.clear();
  delay(1200);
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {

  stateMachine();
  
  if(buttonPushCounter % 2 != 0){
    setDisplay();
  }
  if(buttonPushCounter % 2 == 0 and analogMap <= 0){
    ready();
  }
  if(buttonPushCounter % 2 == 0 and analogMap > 0){
    expose(analogMap);
    resetFunc();
    }
}

//-------------------------------------------------
// FUNCTIONS FOR THE LOOP
//-------------------------------------------------

void stateMachine() {
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
    } 
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

//------------------------------------------

void ready(){
  lcd.home();
  lcd.print("BOO EXPOSURE BOX");
  lcd.setCursor(0,1);
  lcd.print("    push sel    ");
}

//------------------------------------------

int setTime(){
  digitalWrite(timePotPin, HIGH);
  total = total - readings[readIndex];    //Smoothing>>>>>>>>>>>>>>>>>>>
  readings[readIndex] = analogRead(timeRead);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  
    if (readIndex >= numReadings) {
        readIndex = 0;
    }
  average = total / numReadings;          //Smoothing<<<<<<<<<<<<<<<<<<
  
  analogMap = map(average, 1023, 0, 3600, 0);     //Maps pot val to seconds, 3600s = 1h
  return analogMap;
}

// ------------------------------------------------
void setDisplay(){
       setTime();
       lcd.home();
       lcd.print("----SET TIME----");
       lcd.setCursor(0,1);
       lcd.print("Min  ");
       lcd.print(analogMap / 60);
       lcd.print(":");
       lcd.print(analogMap % 60);
       lcd.setCursor(10,1);
       lcd.print("   Sec");
}

//-------------------------------------------------

void expose(int analogMap){
  lcd.clear();
  delay(200);
   if (analogMap > 0){   
      digitalWrite(timePotPin, LOW);
      ledOn();
     for (analogMap; analogMap >= -1; analogMap--){
   
      delay(1000);
      
       lcd.home();
       lcd.print("----EXPOSING----");
       lcd.setCursor(0,1);
       lcd.print("Min  ");
       lcd.print(analogMap / 60);
       lcd.print(":");
       lcd.print(analogMap % 60);
       lcd.setCursor(10,1);
       lcd.print("   Sec");

       if (digitalRead(buttonPin) > 0) {
        resetFunc();
       }
    }
  }  
}
//-------------------------------------------------

void ledOn(){
  digitalWrite(loadRelay, HIGH);
}

