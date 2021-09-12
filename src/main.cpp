#include <common.h>

extern PubSubClient MQTTclient;

Pump pump1("pump1", 53);
Pump pump2("pump2", 52);
Pump pump3("pump3", 51);
Pump pump4("pump4", 50);
Pump pump5("pump5", 49);
Pump pump6("pump6", 48);
Pump pump7("pump7", 47);
Pump pump8("pump8", 46);

Valve venil1("ventil1", 22);
Valve venil2("ventil2", 23);
Valve venil3("ventil3", 24);
Valve venil4("ventil4", 25);
Valve venil5("ventil5", 26);
Valve venil6("ventil6", 27);
Valve venil7("ventil7", 28);
Valve venil8("ventil8", 29);

TempSensor sensor0("sensor0", A0, 3.85, 1000, 1040);
TempSensor sensor1("sensor1", A1, 3.85, 1000, 1040);
TempSensor sensor2("sensor2", A2, 3.85, 1000, 1050);
TempSensor sensor3("sensor3", A3, 3.85, 1000, 1112);
TempSensor sensor4("sensor4", A4, 3.85, 1000, 1040);
TempSensor sensor5("sensor5", A5, 3.85, 1000, 1040);
TempSensor sensor6("sensor6", A6, 3.85, 1000, 1040);
TempSensor sensor7("sensor7", A7, 3.85, 1000, 1040);

unsigned long now = 0;
unsigned long nextMassage = 0;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  Ethernetinit();
  MQTTInit();
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
        sensor0.MQTTPublishState();
        sensor1.MQTTPublishState();
        sensor2.MQTTPublishState();
        sensor3.MQTTPublishState();
        sensor4.MQTTPublishState();
        sensor5.MQTTPublishState();
        sensor6.MQTTPublishState();
        sensor7.MQTTPublishState();
        nextMassage = now + 2000; //next massage in 2s
      }
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}