#include <OneWire.h>
#include <DallasTemperature.h>

#define ONEWIRE_DATA_PIN 4 //bus for OneWire protocol
#define SALINITY_ANALOG_PIN A0 //bus for analog salinity sensor
#define GREEN_ELECTRODE_PIN 7
#define YELLOW_ELECTRODE_PIN 8

OneWire oneWire(ONEWIRE_DATA_PIN); //define OneWire instance (links to all OneWire devices)
DallasTemperature sensors(&oneWire); //define DallasTemperature sensor and pass in OneWire instance

int sample_voltage;

float raw = 0;
int voltage_in = 5;
float final_voltage = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(GREEN_ELECTRODE_PIN, OUTPUT);
  pinMode(YELLOW_ELECTRODE_PIN, OUTPUT);
  pinMode(SALINITY_ANALOG_PIN, INPUT);

  // Serial monitor for debugging
  Serial.begin(9600);

  // Start up DallasTemperature instance
  sensors.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  // Call sensors.requestTemperatures() to get all sensors on that bus
  sensors.requestTemperatures();

  final_voltage = read_salinity(1000);

  Serial.print("Voltage across electrodes: ");
  Serial.print(final_voltage);
  Serial.print(", Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0)); //print temp byIndex since you can have more than one sensor on the same bus
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));

}

int get_voltage_sample(int ms_between_switch){
  digitalWrite(GREEN_ELECTRODE_PIN, HIGH);
  digitalWrite(YELLOW_ELECTRODE_PIN, LOW);
  delay(ms_between_switch);

  return analogRead(SALINITY_ANALOG_PIN);
}

float read_salinity(int samples){

  float total = 0;

  raw = float(get_voltage_sample(500));

  return (raw / 1021.0) * voltage_in;
}
