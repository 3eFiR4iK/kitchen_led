#ifndef Lamp_h
#define Lamp_h

class Lamp 
{

public:
	uint32_t chekMoveTimer, offBrightnessTimer;
	bool isLEDOn = false;
  bool isModeAuto = false;
	int brigtness = 255;

	Lamp () {
    pinMode(LAMP_PIN, OUTPUT);
    pinMode(MOVE_SENSOR_PIN, INPUT);
    analogWrite(LAMP_PIN, 255);
  }

	void checkAutoMode ()
	{
    if (!this->isModeAuto) {
      this->offBrightnessTimer = millis();
      this->chekMoveTimer = millis(); 
      return;
    }
    
		int sensorValue = digitalRead(MOVE_SENSOR_PIN);

    if (sensorValue == 0) {
      Serial.println(sensorValue);
    }
    
    if (millis() - chekMoveTimer >= CHECK_MOVE_PERIOD) {
			this->chekMoveTimer = millis();
			if (sensorValue == 1) {
			  this->offBrightnessTimer = millis(); 
			}
		}

    if (sensorValue == 0 && this->isLEDOn && (millis() - this->offBrightnessTimer >= OFF_BRIGHTNESS_PERIOD)) {
        this->off();
		    this->offBrightnessTimer = millis(); 
		    this->chekMoveTimer = millis(); 
    }

		if (sensorValue == 1 && !this->isLEDOn) {
		  this->offBrightnessTimer = millis();
			this->on();
		}
	}

	void on ()
	{
		if (analogRead(BRIGHTNESS_SENSOR_PIN) > 150) {
			this->brigtness = 0;
		} else {
			this->brigtness = 130;
		}

		for (int i = 255; i >= this->brigtness; i--) {
		  analogWrite(LAMP_PIN, i);
		  delay(5);
		}

		this->isLEDOn = true;
	}

	void off ()
	{
		for (int i = this->brigtness; i <= 255; i++) {
			analogWrite(LAMP_PIN, i);
			delay(5);
		}
    
		this->isLEDOn = false;
	}

  void switchAutoMode(bool state)
  {
    this->isModeAuto = state;
  }

};

#endif