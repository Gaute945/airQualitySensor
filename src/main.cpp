#include <Arduino.h>
#include <cmath>

// Define the analog pin
const int potentiometerPin = A5;
const int one = 8;
const int two = 9;
const int three = 10;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
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

  float NormalPotValue = normalizeToRange(potValue, 0, 1024, 0, 5);
  Serial.print("Normalized Potentiometer Value: ");
  Serial.println(NormalPotValue);

  // Add a short delay before the next reading
  delay(100);
}