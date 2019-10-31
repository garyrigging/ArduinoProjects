/*
Using Arduino bluetooth controller for Android
controls are as follows: 
  Controls:
    Up : "U"
    Down: "D"
    Right: "R"
    Left: "L"
    X: "C"

Using the Adafruit Metro Mini MCU
*/

#include <SoftwareSerial.h>
SoftwareSerial BTserial(4,5); // HC-06 TX pin > Voltage Divider > Pin 4 \\ RX pin > Direct > Pin 5

const int forward = 3;
const int reverse = 2;
char receivedCommand;
boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  setupBLE();
  setupPins();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  listenForSerial();
  doSerialCommand();
}

void(* resetFunc) (void) = 0;


void setupBLE() {
  Serial.begin(9600);
  BTserial.begin(9600);
}

void setupPins() {
  pinMode(forward, OUTPUT);
  pinMode(reverse, OUTPUT);
  digitalWrite(forward, LOW);
  digitalWrite(reverse, LOW);
}


void listenForSerial() {
  // BLE comms
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTserial.available())
      {  
          //Serial.write(BTserial.read());
          receivedCommand = BTserial.read();
          newData = true;
      }
}

void doSerialCommand() {
  if (newData == true) {
    // do something
    switch(receivedCommand) {
      case 'U':
        goForward();
        break;
      case 'D':
        goBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        quickStop();
        break;
      default:
        quickStop();
        break;
    }
    newData = false;
  }
}

void goForward() {
  Serial.println("TODO: servo position change: Straight");
  Serial.println("going forward");
  digitalWrite(reverse, LOW);
  digitalWrite(forward, HIGH);
}

void goBackward() {
  Serial.println("TODO: servo position change: Straight");
  Serial.println("going backwards");
  digitalWrite(forward, LOW);
  digitalWrite(reverse, HIGH);
  
}

void turnLeft() {
  Serial.println("TODO: servo position change: Left");
}

void turnRight() {
  Serial.println("TODO: servo position change: Right");
}

void quickStop() {
  Serial.println("TODO: servo position change: Straight");
  Serial.println("STOPPPPPIIIIINNNNNGGGGG");
  digitalWrite(forward, LOW);
  digitalWrite(reverse, LOW);
}
