#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* Bluetooth HC-05 */
SoftwareSerial BTSerial(2, 3);   // RX, TX

/*  DS18B20  */
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/*  Buzzer  */
#define BUZZER_PIN 8

/*  Temperature Limit  */
float limitTemp = 40.0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  sensors.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  // If sensor error, send default safe value
  if (temp == -127.00 || temp < -50 || temp > 125) {
    temp = 25.00;
  }

  // Send temperature to MIT App
  BTSerial.println(temp);

  // Show in Serial Monitor
  Serial.print("Temperature: ");
  Serial.println(temp);

  // Buzzer ON if temp high
  if (temp >= limitTemp) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1000);
}