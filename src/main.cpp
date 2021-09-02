#include <common.h>

extern EthernetClient Ethernetclient;

void setup()
{
  Serial.begin(9600);

  Ethernetinit();
  MQTTInit();
}

void loop()
{
  if (Ethernetloop())
  {
    MQTTloop();
  }
}