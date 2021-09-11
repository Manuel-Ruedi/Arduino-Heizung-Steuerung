#include <common.h>

class Valve
{
private:
    Valve();

    String name;
    uint8_t pin;
    bool isRunning = false;
    String topic;

public:
    Valve(const char *name, uint8_t pin);
    ~Valve();

    // Accsessors
    uint8_t getPin();
    bool getStatus();

    //Functions
    void activate();

    void deactivate();

    bool MQTTPublishState();

    bool MQTTSubscribe();

    void handleMQTTCallback(String massage);
};