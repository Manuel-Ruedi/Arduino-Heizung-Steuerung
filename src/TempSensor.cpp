#include <common.h>

TempSensor::TempSensor(String name, int Pin, float tempCoefficient, float baseResistance, float refResistor)
{
    this->name = name;
    this->tempCoefficient = tempCoefficient;
    this->baseResistance = baseResistance;
    this->refResistor = refResistor;
    this->pin = Pin;
    numberOfSamples = 10;
    debugTemp = 20.0;
};

float TempSensor::getTemp()
{
    analogReadResolution(12);
    float averageReading = 0;
    float samples[numberOfSamples];

    digitalWrite(11, HIGH);
    for (int i = 0; i < numberOfSamples; i++)
    {
        delay(5);
        samples[i] = analogRead(pin);
    }
    digitalWrite(11, LOW);

    for (int i = 0; i < numberOfSamples; i++)
    {
        averageReading += samples[i];
    }
    averageReading /= numberOfSamples;

    float VtempSensor = (averageReading / 4095) * 3.3;
    float VrefResistor = 3.3 - VtempSensor;
    float current = VrefResistor / refResistor;
    float tempSensorResistanz = VtempSensor / current;
    float temp = (tempSensorResistanz - baseResistance) / tempCoefficient;

    // Serial.print(name + " --> ");
    // Serial.print(tempSensorResistanz);
    // Serial.print(" -- ");
    // Serial.println(temp);
    return temp;
};

bool TempSensor::MQTTPublishState()
{
    String topic("heizung/temp/" + name);

    String payload = String(getTemp());

    return MQTTclient.publish(topic.c_str(), payload.c_str());
}