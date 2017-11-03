int tempValue;
// variable to hold sensor value
int sensorValue;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;
// LED pin
const int ledPin = 13;
// photoresistor pin
const int photoResistorPin = A3;
// temperature pin
const int temperaturePin = A4;

void setup() {
  Serial.begin(9600);
  // Make the LED pin an output and turn it on
  pinMode(ledPin, OUTPUT);
  pinMode(photoResistorPin, INPUT);
  pinMode(temperaturePin, INPUT);
  digitalWrite(ledPin, HIGH);

  // calibrate for the first five seconds after program runs
//   while (millis() < 5000) {
//     // record the maximum sensor value
//     sensorValue = analogRead(photoResistorPin);
//     if (sensorValue > sensorHigh) {
//       sensorHigh = sensorValue;
//     }
//     // record the minimum sensor value
//     if (sensorValue < sensorLow) {
//       sensorLow = sensorValue;
//     }
//   }

  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(photoResistorPin);
  tempValue = analogRead(temperaturePin);
  Serial.print("Temperature value: ");
  Serial.print(tempValue);
  Serial.print(", Sensor value: ");
  Serial.print(sensorValue);
  Serial.print(", Sensor value low: ");
  Serial.print(sensorLow);
  Serial.print(", Sensor value high: ");
  Serial.println(sensorHigh);
  // map the sensor values to a wide range of pitches
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  // play the tone for 20 ms on pin 8
  tone(8, pitch, 20);

  // wait for a moment
  delay(10);
}
