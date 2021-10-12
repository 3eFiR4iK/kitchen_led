bool isLEDOn = false;
int led_pin = 3;
int brigtness = 255;

/** init timer vars */
uint32_t chekMoveTimer, offBrightnessTimer;
uint32_t offBrightnessPeriod = 90000; // 1.5 min
uint32_t chekMovePeriod = 2000; // 2 sec

void setup() {
  pinMode(led_pin, OUTPUT);
}

void loop() {

  int sensorValue = digitalRead(4);

  if (sensorValue == 1 && !isLEDOn) {
      turnOn();
      offBrightnessTimer = millis(); 
      chekMoveTimer = millis(); 
  }

  if (millis() - chekMoveTimer >= chekMovePeriod) {
    chekMoveTimer = millis();
    if (sensorValue == 1) {
      offBrightnessTimer = millis(); 
    }
  }

  if (isLEDOn && (millis() - offBrightnessTimer >= offBrightnessPeriod)) {
    offBrightnessTimer = millis();
    turnOff();
  }

}

void turnOn() {
  if (analogRead(A0) > 150) {
    brigtness = 255;
  } else {
    brigtness = 130;
  }

  for(int i = 0; i <= brigtness; i++) {
      analogWrite(led_pin, i);
      delay(5);
  }
  isLEDOn = true;
}

void turnOff() {
  for(int i = brigtness; i >= 0; i--) {
    analogWrite(led_pin, i);
    delay(5);
  }
  isLEDOn = false;
}
  