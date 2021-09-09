#include <common.h>

Pump pump1("pump1", 22);
Pump pump2("pump2", 23);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  Ethernetinit();
  if (MQTTInit())
  {
    pump1.MQTTSubscribe();
    pump2.MQTTSubscribe();
  }
}

void loop()
{
  if (Ethernetloop())
  {
    if (MQTTloop())
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}