#include <Arduino.h>

// Define the analog pin
const int potentiometerPin = A5;
const int one = 1;
const int two = 2;
const int three = 3;
const int four = 4;
const int five = 5;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(five, OUTPUT);
}

float normalizeToRange(int value, int old_min, int old_max, int new_min, int new_max) {
    float normalized_value = (float)(value - old_min) / (old_max - old_min) * (new_max - new_min) + new_min;  
    
    int rounded_value = (int)round(normalized_value);

    return rounded_value;
}

void loop() {
  // Read the analog value from the potentiometer
  int potValue = analogRead(potentiometerPin);
  
  // Print the value to the Serial Monitor
  // Serial.print("Potentiometer Value: ");
  // Serial.println(potValue);

  int NormalPotValue = normalizeToRange(potValue, 0, 1024, 0, 5);
  Serial.print("Normalized Potentiometer Value: ");
  Serial.println(NormalPotValue);

  switch (NormalPotValue)
  {
  case 1:
    digitalWrite(one, HIGH);
    break;

  case 2:
    digitalWrite(two, HIGH);
    break;

  case 3:
    digitalWrite(three, HIGH);
    break;

  case 4:
    digitalWrite(four, HIGH);
    break;

  case 5:
    digitalWrite(five, HIGH);
    break;
    
  default:
    break;
  }
}