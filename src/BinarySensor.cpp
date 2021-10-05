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
    if (isOn)
    {
        return MQTTclient.publish(topic.c_str(), "ON", true);
    }
    else
    {
        return MQTTclient.publish(topic.c_str(), "OFF", true);
    }
}

void BinarySensor::updateState()
{
    switch (digitalRead(pin))
    {
    case HIGH:
        if (!isOn)
        {
            isOn = true;
            MQTTPublishState();
        }
        break;
    case LOW:
        if (isOn)
        {
            isOn = false;
            MQTTPublishState();
        }
        break;
    };
}