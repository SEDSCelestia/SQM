#include <LiquidCrystal.h>
#include <Math.h>

#define SENSOR_PIN 21

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

volatile unsigned long pulseCount = 0; // Counter for pulses
unsigned long lastMillis = 0; // Time of the last pulse

void setup() {

  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("SkyQualityMeter");

  lcd.setCursor(0, 1);
  lcd.print("Frequency:");

  pinMode(SENSOR_PIN, INPUT); // Set sensor pin as input
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING); // Attach interrupt to the sensor pin

}

void loop() {

  lcd.setCursor(10,1);

  // Calculate frequency every second
  if (millis() - lastMillis >= 1000) {
    unsigned long frequency = pulseCount; // Get the pulse count as frequency (Hz)
    lcd.print(19.0-2.5*log10(frequency));
    pulseCount = 0; // Reset pulse count
    lastMillis = millis(); // Update last millis
  }
}

// Interrupt service routine to count pulses
void countPulse() {
  pulseCount++; // Increment pulse count
}