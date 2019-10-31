
// Variable Definitions
//-----------------------
// Pin Definitions 

int sens = 2; // pin 2 provides voltage to the sensor
int sensRead = 3; // pin 3 used as analogRead on sensor
int water = 4; // pin 4 provides voltage to the water switch

// Sensor Value 

int moistureValue; // to be assigned the value of pin 3 - moistureRead

// Soil Ranges - High end - IF X > RANGE THEN ACTION 

int dry = 260; // if 260 < sensor, water and wait way less
int moist = 360; // if 360 < sensor < 400, wait less to water again
int wet = 400; // if sensor > 400, don't water

// FUNCTIONS
//-------------

void(* resetFunc) (void) = 0; //declare reset function at address 0. Call using resetFunc();

int detectMoisture(int Out, int Read){  //declare a function that reads the sensor 5 times, averages resistance
  int avg = 0;

  digitalWrite(Out, HIGH);
  for (int x = 0; x < 10; x ++)
  {
    avg = avg + analogRead(Read);
    delay(50);
    break;
  }
  avg = (avg / 10);
  digitalWrite(Out, LOW);
  return avg;
}

void waterPlants(int wait){
  digitalWrite(water, HIGH);
  delay(300);
  digitalWrite(water, LOW);
  delay(wait);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}

// Main code loop

void loop() {

  // condition 1 : Soil is dry AF
  if (detectMoisture(sens, sensRead) < dry){
     waterPlants(60000); //water plants for 3 seconds then wait 1 minute
     resetFunc(); // reset
  } else if (detectMoisture(sens, sensRead) > dry && detectMoisture(sens, sensRead) < moist){
    waterPlants(600000); //water plants for 3 seconds then wait 10 minutes
    resetFunc();
  } else if (detectMoisture(sens, sensRead) > moist && detectMoisture(sens, sensRead) < wet){
    delay(1800000); //wait 30 minutes
    resetFunc(); 
  } else if (detectMoisture(sens, sensRead) > wet){
    delay(10800000); // wait 3 hours
    resetFunc();
  }
}



