#include <common.h>

class Valve
{
private:
    Valve();

    String name;
    uint8_t pin;
    bool isRunning;

public:
    Valve(const char *name, uint8_t pin);

    // Accsessors
    uint8_t getPin();
    bool getStatus();

    //Functions
    void activate();

    void deactivate();

    bool MQTTPublishState();

    bool MQTTSubscribe();
};