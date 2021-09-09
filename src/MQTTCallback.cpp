#include <common.h>

extern Pump pump1;
extern Pump pump2;

void MQTTcallback(char *topic, byte *payload, unsigned int length)
{
    String S_topic = String(topic);
    String message = ((char *)payload);
    message.remove(length);
    message.toLowerCase();
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] = ");
    Serial.println(message);
    if (S_topic.startsWith("heizung/pumpen/"))
    {
        if (S_topic.startsWith("heizung/pumpen/pump1"))
        {
            pump1.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/pumpen/pump2"))
        {
            pump2.handleMQTTCallback(message);
        }
    }
}