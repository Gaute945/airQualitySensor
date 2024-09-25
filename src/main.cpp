#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <DHT.h>

// Define the pin where the DHT sensor is connected
#define DHTPIN 2     // Pin connected to the data pin of the DHT sensor

// Choose the sensor type: DHT11 or DHT22
#define DHTTYPE DHT11  // Change to DHT22 if you're using the DHT22 sensor

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

const int gasPin = A5;  // Analog pin A0
int gasValue = 0;

const int butPin = 8;
// 1 for temperature, 2 for humidity, 3 for gas
int currentMode = 1;

const int tempHumSen = 2;

const int ledPin = 7;
const int numPixels = 5;
const int delayVal = 100;

const int potentiometerPin = A5;

int lastLed = 2;
int butMode = 1;

Adafruit_NeoPixel pixels(numPixels, ledPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(butPin, INPUT);
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
  // Read the analog value from the gas sensor
  gasValue = analogRead(gasPin);

  // kalibrert til 50%
  // Read the humidity and temperature (Celsius)
  float humidity = dht.readHumidity();
  // float humidity = 50;

  // float temperatureC = 22;
  float temperatureC = dht.readTemperature();

  int buttonState = digitalRead(butPin);
  if (buttonState == 0) {
    currentMode++;
    if (currentMode > 3) {
      currentMode = 1;
    }
    delay(200);
  }

  // kalibrert til 22C
  // int NormalValue = normalizeToRange(temperatureC, 0, 25, 0, 5);
  // int NormalValue = normalizeToRange(humidity, 0, 100, 0, 5);
  // int NormalValue = normalizeToRange(gasValue, 0, 300, 0, 5);

  // Select NormalValue based on the currentMode
  int NormalValue;
  switch (currentMode) {
    case 1:
      NormalValue = normalizeToRange(temperatureC, 0, 30, 0, 5); // Temperature mode
      Serial.print("temperature");
      Serial.print("\n");
      Serial.print(temperatureC);
      Serial.print("\n");
      break;
    case 2:
      NormalValue = normalizeToRange(humidity, 0, 100, 0, 5); // Humidity mode
      Serial.print("humidity");
      Serial.print("\n");
      break;
    case 3:
      NormalValue = normalizeToRange(gasValue, 0, 300, 0, 5); // Gas mode
      Serial.print("C02");
      Serial.print("\n");
      break;
    default:
      NormalValue = 1; // Fallback in case of an error
      break;
  }

  pixels.clear(); // Clear the pixel buffer

  // Serial.print(currentMode);
  // Serial.print("\n");

  switch (NormalValue)
  {
  case 1:
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.show();
    break;

  case 2:
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      pixels.setPixelColor(1, pixels.Color(0, 0, 255));
      pixels.show();
    break;

  case 3:
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.setPixelColor(1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(2, pixels.Color(0, 255, 0));
      pixels.show();
    break;

  case 4:
      pixels.setPixelColor(0, pixels.Color(255, 255, 0));
      pixels.setPixelColor(1, pixels.Color(255, 255, 0));
      pixels.setPixelColor(2, pixels.Color(255, 255, 0));
      pixels.setPixelColor(3, pixels.Color(255, 255, 0));
      pixels.show();
    break;

  case 5:
      pixels.setPixelColor(0, pixels.Color(0, 255, 255));
      pixels.setPixelColor(1, pixels.Color(0, 255, 255));
      pixels.setPixelColor(2, pixels.Color(0, 255, 255));
      pixels.setPixelColor(3, pixels.Color(0, 255, 255));
      pixels.setPixelColor(4, pixels.Color(0, 255, 255));
      pixels.show();
    break;

  default:
    break;
  }
}
