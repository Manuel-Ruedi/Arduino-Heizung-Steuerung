#include <common.h>

BinarySensor::BinarySensor(String name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    pinMode(pin, INPUT);
    topic = String("heizung/binarysensor/" + this->name);
};

bool BinarySensor::MQTTPublishState()
{
    switch (digitalRead(pin))
    {
    case HIGH:
        MQTTclient.publish(topic.c_str(), "ON");
        break;
    case LOW:
        MQTTclient.publish(topic.c_str(), "OFF");
        break;
    default:
        break;
    };
    return false;
}