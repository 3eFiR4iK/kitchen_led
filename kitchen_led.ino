#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Env.h>
#include <Lamp.h>

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

Lamp lamp;
BlynkTimer timer;

BLYNK_WRITE(V0)
{
  switch (V0) {
    case 0:
      lamp.off(); 
      break;
    case 1:
      lamp.on(); 
      break;
    case 2:

      break;
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  lamp = new Lamp();
}

void loop()
{
  Blynk.run();
}
  