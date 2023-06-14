#include<LiquidCrystal.h>
LiquidCrystal lcd (13, 12, 11, 10, 9, 8);

const float VOLTAGE_REFERENCE = 5.0;     // Reference voltage in volts
const float MAX_VOLTAGE = 6.2;           // Maximum voltage input in volts
const float MAX_WIND_SPEED_KMH = 100.0;  // Maximum wind speed in km/h

const float METER_PER_SECOND_CONVERSION = 0.277778;  // Conversion factor from km/h to m/s

const int WIND_SENSOR_PIN = A0;
const int NUM_READINGS = 1;  // Number of readings to average

float readings[NUM_READINGS];  // Array to store the readings
int index = 0;  // Index of the current reading

void setup() {
  lcd.begin (16, 2);
  Serial.begin (9600);
  
  pinMode(A0, INPUT);
  
  lcd.setCursor (0,0);
  lcd.print("Wind speed : ");
 

  // Initialize the readings array with 0
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Read the voltage input on pin A0
  int sensorValue = analogRead(WIND_SENSOR_PIN);

  // Convert sensor value to voltage
  float voltage = (sensorValue / 1023.0) * VOLTAGE_REFERENCE;

  // Store the reading in the array
  readings[index] = voltage;

  // Increment the index
  index++;
  if (index >= NUM_READINGS) {
    index = 0;  // Wrap around to the beginning of the array
  }

  // Calculate the average voltage
  float averageVoltage = 0;
  for (int i = 0; i < NUM_READINGS; i++) {
    averageVoltage += readings[i];
  }
  averageVoltage /= NUM_READINGS;

  // Convert average voltage to wind speed in km/h
  float windSpeedKMH = (averageVoltage / MAX_VOLTAGE) * MAX_WIND_SPEED_KMH;

  // Convert wind speed to m/s
  float windSpeedMS = windSpeedKMH * METER_PER_SECOND_CONVERSION - 1.20;

  // Print the voltage and wind speed
  
 lcd.setCursor(2,2);
  lcd.print(windSpeedMS, 2);   // Print wind speed with 2 decimal places
  
  lcd.println( "m/s");

  delay(500);  // Delay for 1 second
}
