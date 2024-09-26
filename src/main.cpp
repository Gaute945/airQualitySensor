#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int gasPin = A5;
int gasValue = 0;

const int butPin = 8;
int currentMode = 1;

const int ledPin = 7;
const int numPixels = 5;
const int delayVal = 100;

Adafruit_NeoPixel pixels(numPixels, ledPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(butPin, INPUT);
  // Initialize the NeoPixel strip
  // Start NeoPixel strip
  pixels.begin();
}

float normalizeToRange(int value, int old_min, int old_max, int new_min, int new_max)
{
  float normalized_value = (float)(value - old_min) / (old_max - old_min) * (new_max - new_min) + new_min;
  int rounded_value = (int)round(normalized_value);
  return rounded_value;
}

void loop()
{
  // Read sensor values
  // Les av sensor verdier
  gasValue = analogRead(gasPin);
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();

  // Button press to change mode
  // Knapp trykk forandrer modus
  int buttonState = digitalRead(butPin);
  if (buttonState == 0) {
    currentMode++;
    if (currentMode > 3) {
      currentMode = 1;
    }
    delay(200);
  }

  // Normalize values
  // Normaliser verdier
  int NormalValue;
  switch (currentMode) {
    case 1:
      NormalValue = normalizeToRange(temperatureC, 0, 30, 0, 5); // Temperature
      Serial.print("Temperature: ");
      Serial.println(temperatureC);
      break;
    case 2:
      NormalValue = normalizeToRange(humidity, 0, 90, 0, 5); // Humidity
      Serial.print("Humidity: ");
      Serial.println(humidity);
      break;
    case 3:
      NormalValue = normalizeToRange(gasValue, 0, 300, 0, 5); // Gas (CO2)
      Serial.print("CO2: ");
      Serial.println(gasValue);
      break;
    default:
      NormalValue = 1;
      break;
  }

  pixels.clear();

  // Set color based on currentMode
  // Bytt farge basert paa currentMode
  uint32_t color;
  if (currentMode == 1) {
    color = pixels.Color(255, 100, 0); // Orange for Temperature
  } else if (currentMode == 2) {
    color = pixels.Color(0, 0, 255); // Blue for Humidity
  } else if (currentMode == 3) {
    color = pixels.Color(255, 255, 255); // White for Gas (CO2)
  }

  // Light up LEDs based on NormalValue
  // Bruk mengden LEDs basert paa NormalValue
  for (int i = 0; i < NormalValue; i++) {
    pixels.setPixelColor(i, color);
  }

  // Show the updated LEDs
  // Vis updatert LEDs
  pixels.show();
}

