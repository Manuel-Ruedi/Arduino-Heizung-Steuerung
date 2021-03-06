#include <common.h>

//Constructor

Pump::Pump(const char *name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    String topic("heizung/pumpen/" + this->name);
    pinMode(pin, OUTPUT);
}

Pump::~Pump()
{
    MQTTclient.unsubscribe(topic.c_str());
}

// Accsessors
uint8_t Pump::getPin() { return this->pin; }
bool Pump::getStatus() { return this->isRunning; }

//Functions
void Pump::activate()
{
    if (!isRunning)
    {
        digitalWrite(this->pin, HIGH);
        this->isRunning = true;
    }
}

void Pump::deactivate()
{
    if (isRunning)
    {
        digitalWrite(this->pin, LOW);
        this->isRunning = false;
    }
}

bool Pump::MQTTSubscribe()
{
    String topic(this->topic + "/set");
    return MQTTclient.subscribe(topic.c_str());
}

bool Pump::MQTTPublishState()
{
    String topic(this->topic + "/status");

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

void Pump::handleMQTTCallback(String massage)
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