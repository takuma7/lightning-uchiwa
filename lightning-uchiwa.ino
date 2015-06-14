#include <Filters.h>

#define UPDATE_FREQ (200)

#define ANALOG_MAX (1024)
#define V_MAX (3.3)
#define THRESHOLD (0.7)

int sensorPin = A0;
int ledPin0 = 8;
int ledPin1 = 9;
float rawVal = 0;
float filteredVal = 0;
float pFilteredVal = 0;
float dVal = 0;
float dFilteredVal = 0;

float filterFrequency = 5.0;
float filterFrequency2 = 2.0;
float filterFrequency3 = 2.0;
FilterOnePole lowpassFilter(LOWPASS, filterFrequency);
FilterOnePole lowpassFilter2(LOWPASS, filterFrequency2);
FilterOnePole lowpassFilter3(LOWPASS, filterFrequency3);

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  Serial.begin(115200);  // won't work in 8pino
  while(true){
    delay(1000/UPDATE_FREQ);
    rawVal = analogRead(sensorPin)/(float)ANALOG_MAX;
    lowpassFilter.input(rawVal);
    filteredVal = lowpassFilter.output();
    dVal = fabs(filteredVal - pFilteredVal)*10;
    lowpassFilter2.input(dVal);
    lowpassFilter3.input(lowpassFilter2.output()*3);
    dFilteredVal = lowpassFilter3.output();
    
    if(dFilteredVal > THRESHOLD){
      digitalWrite(ledPin0, HIGH);
      digitalWrite(ledPin1, HIGH);
    }else{
      digitalWrite(ledPin0, LOW);
      digitalWrite(ledPin1, LOW);
    }
    
    //print
    Serial.print(rawVal);
    Serial.print(",");
    Serial.print(filteredVal);
    Serial.print(",");
    Serial.print(dVal);
    Serial.print(",");
    Serial.print(dFilteredVal);
    Serial.print("\r\n");
    pFilteredVal = rawVal;
  }
}

void loop(){
}
