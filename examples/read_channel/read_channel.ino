#define REG_EN 13

#include <MAX11254.h>
#include <elapsedMillis.h>

MAX11254 adc;
elapsedMillis scaleTimer;

void setup() {
  Serial.begin(115200);             // start serial communication
  adc.begin(21);                    // start MAX11254 with PIN 21 for CS
  resetPeripherals();

  adc.writeCTRL1(0b10000101);       // self-calibration, offset binary, continuous cycles
  adc.writeCTRL2(0b00101111);       // internal LDO, PGA enable, 128 gain
  adc.writeCTRL3(0b00000000);       // calibration settings
  adc.writeSEQ(0b00000001);         // ready bar enable

  adc.conversionCommand(0b110110);  // SEQ conversion, 125 sps
}

void loop() {
  adc.readDATA0();
  Serial.println();
  delay(10);
}

void resetPeripherals() {
  pinMode(REG_EN, OUTPUT);
  digitalWrite(REG_EN, LOW);
  delay(20);
  digitalWrite(REG_EN, HIGH);
  delay(20);
}
