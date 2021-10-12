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
  Serial.print("virtual pin =");
  Serial.println(value); 
  switch (value) {
    case 0:
      lamp.off();
      lamp.switchAutoMode(false);
      Serial.println("lamp Off"); 
      break;
    case 1:
      lamp.on();
      Serial.println("lamp On");
      lamp.switchAutoMode(false);
      break;
    case 2:
      lamp.switchAutoMode(true);
      Serial.println("lamp Auto");
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
  