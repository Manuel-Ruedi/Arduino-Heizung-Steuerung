#include <common.h>

//Constructor

Valve::Valve(const char *name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    String topic("heizung/pumpen/" + this->name + "/set");
    pinMode(pin, OUTPUT);
}

Valve::~Valve()
{
    MQTTclient.unsubscribe(topic.c_str());
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
        payload = "ON";
    }
    else
    {
        payload = "OFF";
    }

    return MQTTclient.publish(topic.c_str(), payload.c_str());
}

bool Valve::MQTTSubscribe()
{
    String topic("heizung/ventile/" + name + "/set");

    return MQTTclient.subscribe(topic.c_str());
}

void Valve::handleMQTTCallback(String massage)
{
    if (massage == "on")
    {
        activate();
    }
    else if (massage == "off")
    {
        deactivate();
    }

    MQTTPublishState();
}