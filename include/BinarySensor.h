#include <common.h>

class BinarySensor
{
private:
    BinarySensor();

    String name;
    uint8_t pin;
    String topic;

public:
    BinarySensor(String name, uint8_t pin);

    //Functions
    bool MQTTPublishState();
};