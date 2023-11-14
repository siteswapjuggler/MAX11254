#include <MAX11254.h>

#define CS_PIN 21

MAX11254 adc;
uint32_t adcValues[6];

void setup() {
  Serial.begin(115200);                // start serial communication
  adc.begin(CS_PIN);                   // start MAX11254 with appropriate CS pin
}

void loop() {
  for (byte i = 0; i < 6; i++) {
    adcValues[i] = adc.analogRead(i);
  }

  for (byte i = 0; i < 6; i++) {
    Serial.print(adcValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  delay(10);
}