int tempValue;
int tempStartValue = 0;
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

enum notes {
  NOTE1,
  NOTE2,
  NOTE3,
  NOTE4
};

void setup() {
  Serial.begin(9600);
  // Make the LED pin an output and turn it on
  pinMode(ledPin, OUTPUT);
  pinMode(photoResistorPin, INPUT);
  pinMode(temperaturePin, INPUT);
  digitalWrite(ledPin, HIGH);

  tempStartValue = analogRead(temperaturePin);

  // calibrate for the first five seconds after program runs
  while (millis() < 5000) {
    // record the maximum sensor value
    sensorValue = analogRead(photoResistorPin);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }

  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(photoResistorPin);
  tempValue = analogRead(temperaturePin);

  notes freq = calculateFreq(tempValue);

  Serial.print("Temperature value: ");
  Serial.print(tempValue);
  Serial.print(", Temperature freq: ");
  Serial.print(freq);
  Serial.print(", Temperature start value: ");
  Serial.print(tempStartValue);
  Serial.print(", Sensor value: ");
  Serial.print(sensorValue);
  Serial.print(", Sensor value low: ");
  Serial.print(sensorLow);
  Serial.print(", Sensor value high: ");
  Serial.println(sensorHigh);

  // map the sensor values to a wide range of pitches
  int pitch = 50;

  switch (freq) {
    case NOTE1:
      pitch = map(sensorValue, sensorLow, sensorHigh, 50, 500);
      break;
    case NOTE2:
      pitch = map(sensorValue, sensorLow, sensorHigh, 501, 1000);
      break;
    case NOTE3:
      pitch = map(sensorValue, sensorLow, sensorHigh, 1001, 2000);
      break;
    case NOTE4:
      pitch = map(sensorValue, sensorLow, sensorHigh, 2001, 3000);
      break;
    default:
      pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
    break;
  }

  // play the tone for 20 ms on pin 8
  tone(8, pitch, 20);

  // wait for a moment
  delay(10);
}

notes calculateFreq(int value) {
  if(value - tempStartValue >= 3 && value - tempStartValue < 5) {
    return NOTE2;
  } else if(value - tempStartValue >= 5 && value - tempStartValue < 7) {
    return NOTE3;
  } else if(value - tempStartValue >= 7) {
    return NOTE4;
  } else {
    return NOTE1;
  }
}
