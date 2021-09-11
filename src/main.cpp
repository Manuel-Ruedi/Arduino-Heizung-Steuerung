#include <common.h>

extern PubSubClient MQTTclient;

Pump pump1("pump1", 22);
Pump pump2("pump2", 23);

Valve venil1("ventil1", 24);
Valve venil2("ventil2", 25);
Valve venil3("ventil3", 26);
Valve venil4("ventil4", 27);
Valve venil5("ventil5", 28);
Valve venil6("ventil6", 29);

TempSensor sensor0("sensor0", A0, 3.85, 1000, 1040);
TempSensor sensor1("sensor1", A1, 3.85, 1000, 1090);
TempSensor sensor2("sensor2", A2, 3.85, 1000, 1050);
TempSensor sensor3("sensor3", A3, 3.85, 1000, 1112);

unsigned long now = 0;
unsigned long nextMassage = 0;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  Ethernetinit();
  if (MQTTInit())
  {
    pump1.MQTTSubscribe();
    pump1.MQTTPublishState();
    pump2.MQTTSubscribe();
    pump2.MQTTPublishState();

    venil1.MQTTSubscribe();
    venil1.MQTTPublishState();
    venil2.MQTTSubscribe();
    venil2.MQTTPublishState();
    venil3.MQTTSubscribe();
    venil3.MQTTPublishState();
    venil4.MQTTSubscribe();
    venil4.MQTTPublishState();
    venil5.MQTTSubscribe();
    venil5.MQTTPublishState();
    venil6.MQTTSubscribe();
    venil6.MQTTPublishState();
  }
}

void loop()
{
now = millis();
if (Ethernetloop())
{
  if (MQTTloop())
  {
    digitalWrite(LED_BUILTIN, HIGH);
    if (now > nextMassage)
    {
      sensor2.MQTTPublishState();
      sensor3.MQTTPublishState();
      nextMassage = now + 2000; //next massage in 2s
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
}