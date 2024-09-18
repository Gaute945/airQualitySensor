#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int butPin = 9;

const int pin = 8;
const int numPixels = 5;
const int delayVal = 100;

const int potentiometerPin = A5;

int lastLed = 2;

Adafruit_NeoPixel pixels(numPixels, pin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  pinMode(butPin, OUTPUT);
  pixels.begin(); // Initialize the NeoPixel strip
}

float normalizeToRange(int value, int old_min, int old_max, int new_min, int new_max)
{
  float normalized_value = (float)(value - old_min) / (old_max - old_min) * (new_max - new_min) + new_min;
  int rounded_value = (int)round(normalized_value);
  return rounded_value;
}

void loop()
{
  int butOut = digitalRead(butPin);
  Serial.print(butOut);

  int potValue = analogRead(potentiometerPin);
  int NormalPotValue = normalizeToRange(potValue, 0, 1023, 0, 5);
  Serial.print("Normalized Potentiometer Value: ");
  Serial.println(NormalPotValue);
  
  pixels.clear(); // Clear the pixel buffer

  switch (NormalPotValue)
  {
  case 1:
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    break;

  case 2:
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.show();
    break;

  case 3:
    pixels.setPixelColor(2, pixels.Color(0, 0, 255));
    pixels.show();
    break;

  case 4:
    pixels.setPixelColor(3, pixels.Color(255, 255, 0));
    pixels.show();
    break;

  case 5:
    pixels.setPixelColor(4, pixels.Color(0, 255, 255));
    pixels.show();
    break;

  default:
    break;
  }
}