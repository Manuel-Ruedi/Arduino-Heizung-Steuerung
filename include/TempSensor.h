#include <common.h>

class TempSensor
{
private:
    TempSensor();

    String name;
    float tempCoefficient;
    float baseResistance;
    float refResistor;
    int pin;
    int numberOfSamples = 10;
    float debugTemp = 20.0;

public:
    TempSensor(String name, int Pin, float tempCoefficient, float baseResistance, float refResistor);

    float getTemp();

    bool MQTTPublishState();
};
