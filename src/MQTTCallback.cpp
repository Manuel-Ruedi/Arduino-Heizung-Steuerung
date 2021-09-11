#include <common.h>

extern Pump pump1;
extern Pump pump2;
extern Valve venil1;
extern Valve venil2;
extern Valve venil3;
extern Valve venil4;
extern Valve venil5;
extern Valve venil6;

void MQTTcallback(char *topic, byte *payload, unsigned int length)
{
    String S_topic = String(topic);
    String message = ((char *)payload);
    message.remove(length);
    message.toLowerCase();
    // Serial.print("Message arrived [");
    // Serial.print(topic);
    // Serial.print("] = ");
    // Serial.println(message);
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
    else if (S_topic.startsWith("heizung/ventile"))
    {
        if (S_topic.startsWith("heizung/ventile/ventil1"))
        {
            venil1.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/ventile/ventil2"))
        {
            venil2.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/ventile/ventil3"))
        {
            venil3.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/ventile/ventil4"))
        {
            venil4.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/ventile/ventil5"))
        {
            venil5.handleMQTTCallback(message);
        }
        else if (S_topic.startsWith("heizung/ventile/ventil6"))
        {
            venil6.handleMQTTCallback(message);
        }
    }
}