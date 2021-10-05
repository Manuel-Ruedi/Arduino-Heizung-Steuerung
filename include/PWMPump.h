#include <common.h>

class PWMPump
{
private:
    PWMPump();

    String name;
    uint8_t pin;
    u_int8_t speed = 0;
    String topic;

public:
    PWMPump(const char *name, uint8_t pin);
    ~PWMPump();

    // Accsessors
    uint8_t getPin();
    uint8_t getSpeed();

    //Functions
    void SetSpeed(uint8_t NewSpeed);

    bool MQTTSubscribe();

    bool MQTTPublishState();

    void handleMQTTCallback(String massage);
};