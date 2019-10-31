#include "pitches.h"

#define buttonOne 2 // button one is on pin 2
#define buttonTwo 3 // button two is on pin 3
#define buzzer 8 // the piezo buzzer is on pin 4
#define ledOne 5 // button 1 led on pin 5
#define ledTwo 6 // button 2 led on pin 6
#define lockTime 5000 // lockout time before can play again
#define nd 300 // note duration
#define pMultiply 1.30 // pause duration multiplier


void lockout(unsigned long del){
    delay(del);
}

void playMelody(){
  // notes in the melody:
  int melody[] = {

    NOTE_G5, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_G5, NOTE_G4
    /* NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS4, 
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4,
    
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_C5, 
    NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_G5,
    NOTE_DS6,NOTE_DS6,NOTE_DS6, NOTE_C6,
    
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_B5, 
    NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_G5,
    NOTE_F6, NOTE_F6, NOTE_F6, NOTE_D6,

    NOTE_G6, NOTE_G6, NOTE_F6, NOTE_DS6,NOTE_D6,
    NOTE_G6, NOTE_G6, NOTE_F6, NOTE_DS6,NOTE_D6,

    NOTE_G6, NOTE_G6, NOTE_F6, NOTE_DS6, 0, 
    NOTE_C6,0, NOTE_G6 */

      
    };
    
    // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    8,8,8,8,8,8,8,8 
    /* 8, 8, 8, 2, 
    8, 8, 8, 2,
    
    8, 8, 8, 8,
    8, 8, 8, 8,
    8, 8, 8, 2,
    
    8, 8, 8, 8, 
    8, 8, 8, 8,
    8, 8, 8, 2,

    8, 8, 8, 2, 8,
    8, 8, 8, 2, 8,

    8, 8, 8, 4, 4,
    4, 4, 2 */
    };

  for (int thisNote = 0; thisNote < 7; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = nd / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * pMultiply;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}

void buttonOneWins() {
  Serial.begin(9600);
  unsigned long currentMillis = millis();
  unsigned long startMillis = currentMillis;
  digitalWrite(ledOne, HIGH);
  digitalWrite(ledTwo, LOW);
  playMelody();
  lockout(lockTime);
  digitalWrite(ledOne, LOW);
  Serial.print(currentMillis);
  Serial.println(startMillis);
  
}

void buttonTwoWins() {
  Serial.begin(9600);
  unsigned long currentMillis = millis();
  unsigned long startMillis = currentMillis;
  digitalWrite(ledTwo, HIGH);
  digitalWrite(ledOne, LOW);
  playMelody();
  lockout(lockTime);
  digitalWrite(ledTwo, LOW);
  Serial.print(currentMillis);
  Serial.println(startMillis);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledOne, LOW);
  digitalWrite(ledTwo, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  int b1;
  int b2;
  int buttonRace[2] = {digitalRead(buttonOne), digitalRead(buttonTwo)};
  b1 = buttonRace[0];
  b2 = buttonRace[1];
  if (b1 == b2){
    loop(); 
  } else if(b1 > b2){
    buttonTwoWins();
  } else if(b2 > b1){
    buttonOneWins();
  }

}
