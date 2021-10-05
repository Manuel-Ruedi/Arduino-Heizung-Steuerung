#pragma once

#include <secret.h>
#include <Arduino.h>

#include <Ethernet.h>
#include <PubSubClient.h>
#include <Pump.h>
#include <PWMPump.h>
#include <Valve.h>
#include <TempSensor.h>
#include <BinarySensor.h>

bool Ethernetinit();
bool Ethernetloop();
bool MQTTInit();
bool MQTTloop();

extern PubSubClient MQTTclient;