#include <common.h>

class Pump
{
private:
    Pump();

    String name;
    uint8_t pin;
    bool isRunning;
    String topic;

public:
    Pump(const char *name, uint8_t pin);
    ~Pump();

    // Accsessors
    uint8_t getPin();
    bool getStatus();

    //Functions
    void activate();

    void deactivate();

    bool MQTTSubscribe();

    bool MQTTPublishState();

    void handleMQTTCallback(String massage);
};