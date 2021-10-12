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
      break;
    case 1:
      lamp.on();
      Serial.println("lamp On");
      break;
    case 2:
      lamp.switchAutoMode(true);
      break;
  }
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  Lamp* lamp = new Lamp();
}

void loop()
{
  Blynk.run();
  lamp.checkAutoMode();
}
  