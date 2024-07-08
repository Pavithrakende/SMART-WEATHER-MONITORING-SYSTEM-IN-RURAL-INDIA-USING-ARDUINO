#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SD.h>
#include <SPI.h>

// Define sensor pins
#define SD_CS_PIN 10 // SD card chip select pin

// Initialize BME280 sensor
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  
  Serial.println("Weather Monitoring System Initialized");
}

void loop() {
  // Read data from sensors
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // hPa to Pa

  // Print data to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Store data in SD card
  File dataFile = SD.open("weather_data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Temperature: ");
    dataFile.print(temperature);
    dataFile.print(" *C, Humidity: ");
    dataFile.print(humidity);
    dataFile.print(" %, Pressure: ");
    dataFile.print(pressure);
    dataFile.println(" Pa");
    dataFile.close();
  } else {
    Serial.println("Error opening file for writing!");
  }

  delay(1000 * 60 * 5); // Sample every 5 minutes (adjust as needed)
}




//1.Libraries: Ensure you have installed the necessary libraries (Adafruit_Sensor and Adafruit_BME280) using the Arduino Library Manager (Sketch > Include Library > Manage Libraries...).
//2.SD Card: Adjust SD_CS_PIN according to your wiring.
//3.Data Logging: Data is logged to an SD card (weather_data.txt) and printed to the serial monitor.
//4.Adjustments: Modify sensor readings and data logging based on your sensor setup and requirements.

//This code provides a basic framework for reading temperature, humidity, and pressure from the BME280 sensor and storing the data locally on an SD card using Arduino Uno. Customize it further by adding more sensors, implementing real-time data transmission using modules like GSM/GPRS, or integrating additional features as required for your project.
