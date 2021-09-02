#pragma once

#include <secret.h>
#include <Arduino.h>

#include <Ethernet.h>
#include <PubSubClient.h>

bool Ethernetinit();
bool Ethernetloop();
bool MQTTInit();
bool MQTTloop();