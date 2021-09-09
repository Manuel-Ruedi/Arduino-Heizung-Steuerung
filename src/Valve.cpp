#include <common.h>

//Constructor

Valve::Valve(const char *name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    this->isRunning = false;
}

// Accsessors
uint8_t Valve::getPin() { return this->pin; }
bool Valve::getStatus() { return this->isRunning; }

//Functions
void Valve::activate()
{
    if (!isRunning)
    {
        digitalWrite(this->pin, HIGH);
        this->isRunning = true;
    }
}

void Valve::deactivate()
{
    if (isRunning)
    {
        digitalWrite(this->pin, LOW);
        this->isRunning = false;
    }
}

bool Valve::MQTTPublishState()
{
    String topic("heizung/ventile/" + name + "/status");

    String payload;

    if (isRunning)
    {
        payload = "on";
    }
    else
    {
        payload = "off";
    }
    Serial.println("publishing: ");
    Serial.print("topic: ");
    Serial.println(topic.c_str());
    Serial.print("payload: ");
    Serial.println(payload.c_str());

    return MQTTclient.publish(topic.c_str(), payload.c_str());
}

bool Valve::MQTTSubscribe()
{
    String topic("heizung/ventile/" + name + "/set");

    return MQTTclient.subscribe(topic.c_str());
}