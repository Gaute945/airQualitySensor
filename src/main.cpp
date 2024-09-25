#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <DHT.h>

// Define the pin where the DHT sensor is connected
#define DHTPIN 2     // Pin connected to the data pin of the DHT sensor

// Choose the sensor type: DHT11 or DHT22
#define DHTTYPE DHT11  // Change to DHT22 if you're using the DHT22 sensor

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

const int butPin = 8;

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
  // Read the humidity and temperature (Celsius)
  float humidity = dht.readHumidity();

  float temperatureC = dht.readTemperature();

  // Print results to the serial monitor
  // Serial.print(humidity);
  
  // Serial.print(temperatureC);
  
  // Serial.print(heatIndexC);

  int buttonState = digitalRead(butPin);

  int NormalValue = normalizeToRange(temperatureC, 0, 40, 0, 5);
  // int NormalValue = normalizeToRange(humidity, 0, 100, 0, 5);

  // Serial.print("Normalized Potentiometer Value: ");
  // Serial.println(NormalPotValue);
  
  pixels.clear(); // Clear the pixel buffer

  Serial.print(NormalValue);

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