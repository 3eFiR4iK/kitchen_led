#ifndef Lamp_h
#define Lamp_h

#include <Env.h>

class Lamp 
{

public:
	uint32_t chekMoveTimer, offBrightnessTimer;
	bool isLEDOn = false;
	int brigtness = 255;

	void Lamp () {}

	void modeAuto ()
	{
		int sensorValue = digitalRead(MOVE_SENSOR_PIN);

		if (sensorValue == 1 && !this.isLEDOn) {
		  this.off();
		  offBrightnessTimer = millis(); 
		  chekMoveTimer = millis(); 
		}

		if (millis() - chekMoveTimer >= CHECK_MOVE_PERIOD) {
			chekMoveTimer = millis();
			if (sensorValue == 1) {
			  offBrightnessTimer = millis(); 
			}
		}

		if (this.isLEDOn && (millis() - offBrightnessTimer >= OFF_BRIGHTNESS_PERIOD)) {
			offBrightnessTimer = millis();
			this.on();
		}
	}

	void on ()
	{
		if (analogRead(BRIGHTNESS_SENSOR_PIN) > 150) {
			this.brigtness = 255;
		} else {
			this.brigtness = 130;
		}

		for(int i = 0; i <= this.brigtness; i++) {
		  analogWrite(LAMP_PIN, i);
		  delay(5);
		}
		this.isLEDOn = true;
	}

	void off ()
	{
		for(int i = this.brigtness; i >= 0; i--) {
			analogWrite(LAMP_PIN, i);
			delay(5);
		}
		this.isLEDOn = false;
	}

}

#endif