#include "Env.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Lamp.h"

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

Lamp lamp;

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  switch (value) {
    case 0:
      lamp.off();
      lamp.switchAutoMode(false);
      debug("lamp off");
      break;
    case 1:
      lamp.on();
      lamp.switchAutoMode(false);
      debug("lamp on");
      break;
    case 2:
      lamp.switchAutoMode(true);
      debug("lamp Auto");
      break;
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Lamp* lamp = new Lamp();
}

void loop()
{
  Blynk.run();
  lamp.checkAutoMode();
}


void debug(char message[])
{
  if (DEBUG) {
    Serial.println(message);
  }
}
  