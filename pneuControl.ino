#include "HX711.h"
HX711 ps; 

const int switch_pin = A1;
const int pumpPin = 3;
const int solenoid1 = 8;
const int pump2 = 4;
const int solenoid2 = 5;
const int pump3 = 9;
const int solenoid3 = 10;
const int sensorPin = A2;
const int ledPin = 13;

const int OUT_ = 6; // OUT data pin
const int SCK_ = 7; // clock data pin

float pressure;
//Q2HX711 MPS20N0040D(MPS_OUT_pin, MPS_SCK_pin); 
void setup() {
  Serial.begin(115200);
  //ps.begin(OUT_, SCK_);
  //ps.set_gain(64);

  pinMode(OUT_, INPUT);   // Connect HX710 OUT to Arduino pin 2
  pinMode(SCK_, OUTPUT);
  pinMode(switch_pin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  if ( digitalRead(switch_pin) == HIGH) {
    digitalWrite(solenoid1,HIGH); // turn pressure valve HIGH
    digitalWrite(pumpPin,HIGH); // make sure pump is on
    digitalWrite(ledPin,HIGH); // LED ON
  }
  if ( digitalRead(switch_pin) == LOW) {
    digitalWrite(solenoid1,LOW); // turn pressure valve HIGH
    digitalWrite(pumpPin,LOW); // pump is off
    digitalWrite(ledPin,LOW); // LED off
  }
  if (ps.is_ready()) {
    pressure = (ps.read() + 8388607) / 93207.00;
    //pressure = scale.read() + 8388607;
    //pressure = ps.read();
    Serial.println(pressure); 
  }
  //Serial.println(5);


  //Serial.println(digitalRead(switch_pin));
  /*
  int sensorValue = analogRead(sensorPin); 
  int mV = (sensorValue/1023 * 5) * 1000 ;
  int pressure = mV / 26.7;
  Serial.print("snsrvalue: ");
  Serial.print(sensorValue);
  Serial.print("pressure: "); 
  Serial.println(pressure);
  int desiredValue = 15;
  int tolerance = 2;

  if (sensorValue <= desiredValue) {
    analogWrite(pumpPin,255); // Pump. (0 is off) and (255 is on)
    digitalWrite(inletValvePin,HIGH); // open the air valve
    digitalWrite(exhaustValvePin,LOW); // close the exhaust valve
  }
  if (sensorValue > desiredValue) {
    while (analogRead(A0) > (desiredValue - tolerance) ) {
      analogWrite(pumpPin,190); // reduce speed of pump
      digitalWrite(inletValvePin,HIGH); // open the air valve
      digitalWrite(exhaustValvePin,LOW); // close the exhaust valve
    }
  }
    */
}
