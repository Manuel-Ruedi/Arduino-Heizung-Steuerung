#pragma once

#include <secret.h>
#include <Arduino.h>

#include <Ethernet.h>
#include <PubSubClient.h>
#include <Pump.h>
#include <Valve.h>
#include <TempSensor.h>

bool Ethernetinit();
bool Ethernetloop();
bool MQTTInit();
bool MQTTloop();

extern PubSubClient MQTTclient;