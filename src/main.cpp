#include <Arduino.h>

// Define the analog pin
const int potentiometerPin = A5;
const int red = 8;
const int green = 9;
const int blue = 10;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // Read the analog value from the potentiometer
  int potValue = analogRead(potentiometerPin);
  
  // Print the value to the Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  
  if (potValue < 500)
  {
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
  }
  

  // Add a short delay before the next reading
  delay(100);
}