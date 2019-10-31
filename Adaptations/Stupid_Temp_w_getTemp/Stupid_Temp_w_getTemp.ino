// which analog pin to connect
#define THERMISTORPIN A0         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 10
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3200
// the value of the 'other' resistor
#define SERIESRESISTOR 10000   
// the output relay pin
#define HEATER 7 
// input pin to sense heater status
#define SENSE 6
// temperature at which to start heating
#define tempSet 75.0
// hysterisis
#define hysterisis 0.0
// safe cool time in half-seconds
#define safeCoolTime 6
 
uint16_t samples[NUMSAMPLES];

float tempRead(){
  uint8_t a;
  float average;
 
  // take N samples in a row, with a slight delay
  for (a=0; a< NUMSAMPLES; a++) {
   samples[a] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (a=0; a< NUMSAMPLES; a++) {
     average += samples[a];
  }
  average /= NUMSAMPLES;
 
  // Serial.print("Average analog reading "); 
  // Serial.println(average);
 
  // convert the value to resistance
  // average = 1023 - average;  // use if PTC
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  // Serial.print("Thermistor resistance "); 
  // Serial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  steinhart = (steinhart * 9.0)/ 5.0 + 32.0;   // convert to F 
  return steinhart;
}

float printTemp(float temperature){
  int hotRead = digitalRead(SENSE);
  Serial.print(temperature);
  Serial.print(" F,");
  if(hotRead == 1) {
    Serial.println("*");
  } else {
    Serial.println("/");
  } 
}

float getTemp(){
  float temperature = tempRead();   
  printTemp(temperature); 
  return temperature;  
}

void safeCool(int sTime){
  digitalWrite(HEATER, LOW); //safety precaution - always turn the heater off for    ****** define this as a safe cool function
  for(int b; b < sTime; b++){
    getTemp();
    delay(500);
  }
}

void heat(){
  int c = 0;
  for (c = 0; c < 12; c++){           // never heat for more than 6 seconds straight
    digitalWrite(HEATER, HIGH);            // trip relay from pin 7 (heat on)                
    delay(500); // wait .5 sec                                     ******define time variable 
    if (getTemp() > (tempSet + hysterisis)){         // 73.08 for a hysterisis of .5 degrees 
      digitalWrite(HEATER, LOW);
      break;
    } 
  }
      safeCool(safeCoolTime);                // 3 seconds after heating
}
 
void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(HEATER, OUTPUT);
  pinMode(SENSE, INPUT);
  digitalWrite(HEATER, LOW);
  Serial.println("Temp,HeatStatus");
}
 
void loop(void) {
  if (getTemp() < tempSet){          // start heating when temp < 73.0                   ******** define temp set variable
    heat();
  } else {
    digitalWrite(HEATER, LOW);
    delay(500);
  }
 
  
}
