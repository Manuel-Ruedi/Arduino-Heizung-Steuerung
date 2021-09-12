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

//  name, pin, steigung ohm/c°, ohm bei 0°C, vorwiderstand in ohm

TempSensor sensor0("sensor0", A0, 4.05, 1000, 1000);
TempSensor sensor1("sensor1", A1, 3.85, 1021, 1000);
TempSensor sensor2("sensor2", A2, 3.85, 972, 1000);
TempSensor sensor3("sensor3", A3, 3.85, 1026, 1000);
TempSensor sensor4("sensor4", A4, 3.85, 1007, 1000);
TempSensor sensor5("sensor5", A5, 3.85, 1004, 1000);
TempSensor sensor6("sensor6", A6, 3.85, 999, 1000);
TempSensor sensor7("sensor7", A7, 3.85, 1021, 1000);

BinarySensor binarySensor0("sensor0", 0);
BinarySensor binarySensor1("sensor1", 1);
BinarySensor binarySensor2("sensor2", 2);
BinarySensor binarySensor3("sensor3", 3);
BinarySensor binarySensor4("sensor4", 4);
BinarySensor binarySensor5("sensor5", 5);
BinarySensor binarySensor6("sensor6", 6);
BinarySensor binarySensor7("sensor7", 7);

unsigned long now = 0;
unsigned long nextMassage = 0;
unsigned long nextSteteCheck = 0;

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
      if (now > nextSteteCheck)
      {

        binarySensor0.updateState();
        binarySensor1.updateState();
        binarySensor2.updateState();
        binarySensor3.updateState();
        binarySensor4.updateState();
        binarySensor5.updateState();
        binarySensor6.updateState();
        binarySensor7.updateState();

        nextSteteCheck = now + 100; //all 0.1s one state check
      }
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}