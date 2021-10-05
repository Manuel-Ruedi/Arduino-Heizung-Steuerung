#include <common.h>

//Constructor

PWMPump::PWMPump(const char *name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    String topic("heizung/PWMPumpen/" + this->name);
    pinMode(pin, OUTPUT);
}

PWMPump::~PWMPump()
{
    MQTTclient.unsubscribe(topic.c_str());
}

// Accsessors
uint8_t PWMPump::getPin() { return this->pin; }
uint8_t PWMPump::getSpeed() { return this->speed; }

//Functions

bool PWMPump::MQTTSubscribe()
{
    String topic(this->topic + "/set");

    return MQTTclient.subscribe(topic.c_str());
}

bool PWMPump::MQTTPublishState()
{
    String payload(speed);
    String topic(this->topic + "/status");

    return MQTTclient.publish(topic.c_str(), payload.c_str());
}

void PWMPump::SetSpeed(uint8_t NewSpeed)
{
    analogWrite(pin, NewSpeed);
    speed = NewSpeed;
}

void PWMPump::handleMQTTCallback(String massage)
{
    uint8_t NewSpeed = massage.toInt();
    if ((NewSpeed >= 0) && (NewSpeed <= 255))
    {
        SetSpeed(NewSpeed);
    }

    MQTTPublishState();
}