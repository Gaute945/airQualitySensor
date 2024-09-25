// Inkluderer DHT-sensorbiblioteket
#include <DHT.h>

// Definerer pin for DHT11-sensoren
#define DHTPIN 2       // Digital pin 2 er koblet til DHT11
#define DHTTYPE DHT11  // Definerer sensortypen som DHT11

// Oppretter et DHT-objekt 
DHT dht(DHTPIN, DHTTYPE);

// Definerer pin for den analoge sensoren
int sensorPin = A1;

void setup() {
  // Starter kommunikasjon med Serial Monitor
  Serial.begin(115200);
  
  // Starter DHT-sensoren for å begynne å lese temperatur og fuktighet
  dht.begin();
}

void loop() {
  // Leser temperaturen i Celsius fra DHT11-sensoren
  float temp = dht.readTemperature();  // Funksjonen returnerer temperaturen i grader Celsius

  // Leser luftfuktigheten fra DHT11-sensoren
  float fuktighet = dht.readHumidity();  // Funksjonen returnerer fuktigheten i prosent (%)

  // Sjekker om lesingene fra sensoren er gyldige
  if (isnan(temp) || isnan(fuktighet)) {
    // Skriver en feilmelding hvis lesingene ikke er gyldige
    Serial.println("Feil ved avlesning fra DHT-sensoren!");
  } else {
    // Skriver ut temperaturen til Serial Monitor
    Serial.print("Temperatur i Celsius: ");
    Serial.print(temp);
    Serial.print("°C");

    // Skriver ut luftfuktigheten til Serial Monitor
    Serial.print("  |  Luftfuktighet: ");
    Serial.print(fuktighet);
    Serial.println(" %");
  }

  // Leser data fra den analoge sensoren (gassensor)
  Serial.print("Analog sensorverdi: ");
  Serial.println(readSensor());

  // Vent 2 sekunder før neste måling
  delay(2000);
}

// Funksjon for å lese den analoge sensoren
int readSensor() {
  int sensorValue = analogRead(sensorPin);               // Leser verdien fra den analoge pinnen
  int outputValue = map(sensorValue, 0, 1023, 0, 255);   // Kartlegger verdien til et skalaområde fra 0 til 255
  return outputValue;                                    // Returnerer den kartlagte verdien
}