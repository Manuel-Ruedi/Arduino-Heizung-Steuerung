#include <common.h>

extern Pump pump2;
extern Pump pump1;
extern Pump pump3;
extern Pump pump4;
extern Pump pump5;
extern Pump pump6;
extern Pump pump7;
extern Pump pump8;

extern Valve venil1;
extern Valve venil2;
extern Valve venil3;
extern Valve venil4;
extern Valve venil5;
extern Valve venil6;
extern Valve venil7;
extern Valve venil8;

extern EthernetClient Ethernetclient;
extern void MQTTcallback(char *topic, byte *payload, unsigned int length);
IPAddress server(192, 168, 0, 201);
PubSubClient MQTTclient(server, 1883, &MQTTcallback, Ethernetclient);

const char Devicename[] = "arduino-heizung";
const char Username[] = MQTTUSERNAME;
const char Password[] = MQTTPASSWORD;

bool MQTTWasDisconnected = false;
bool checkMQTT();

bool MQTTconnect()
{
    if (MQTTclient.connect(Devicename, Username, Password, "heizung/status", 1, true, "offline"))
    {
        MQTTclient.publish("heizung/status", "online", true);
        pump1.MQTTSubscribe();
        pump1.MQTTPublishState();
        pump2.MQTTSubscribe();
        pump2.MQTTPublishState();
        pump3.MQTTSubscribe();
        pump3.MQTTPublishState();
        pump4.MQTTSubscribe();
        pump4.MQTTPublishState();
        pump5.MQTTSubscribe();
        pump5.MQTTPublishState();
        pump6.MQTTSubscribe();
        pump6.MQTTPublishState();
        pump7.MQTTSubscribe();
        pump7.MQTTPublishState();
        pump8.MQTTSubscribe();
        pump8.MQTTPublishState();

        venil1.MQTTSubscribe();
        venil1.MQTTPublishState();
        venil2.MQTTSubscribe();
        venil2.MQTTPublishState();
        venil3.MQTTSubscribe();
        venil3.MQTTPublishState();
        venil4.MQTTSubscribe();
        venil4.MQTTPublishState();
        venil5.MQTTSubscribe();
        venil5.MQTTPublishState();
        venil6.MQTTSubscribe();
        venil6.MQTTPublishState();
        venil7.MQTTSubscribe();
        venil7.MQTTPublishState();
        venil8.MQTTSubscribe();
        venil8.MQTTPublishState();

        return true;
    }
    else
        return false;
}

bool MQTTInit()
{
    Serial.print("Connecting MQTT-client...");
    if (MQTTconnect())
    {
        Serial.println("connected");
        return true;
    }
    else
    {
        Serial.println("failed!");
        return false;
    }
}

bool MQTTloop()
{
    if (checkMQTT())
    {
        MQTTclient.loop();
        return true;
    }
    else
    {
        return false;
    }
};

bool checkMQTT()
{
    if (MQTTclient.state() == 0) //everything ok
    {
        if (MQTTWasDisconnected)
        {
            Serial.println("The MQTT-client is connected.");
            MQTTWasDisconnected = false;
        }
        return true;
    }
    else if (MQTTWasDisconnected)
    {
        if (MQTTconnect())
        {
            Serial.println("MQTT-client reconnected!");
            MQTTWasDisconnected = false;
            return true;
        }
        else
            return false;
    }
    else
    {
        Serial.print("MQTT: ");
        switch (MQTTclient.state())
        {
        case -4:
            Serial.println("the server didn't respond within the keepalive time");
            break;
        case -3:
            Serial.println("the network connection was broken");
            break;
        case -2:
            Serial.println("the network connection failed");
            break;
        case -1:
            Serial.println("the client is disconnected cleanly");
            break;
        case 1:
            Serial.println("the server doesn't support the requested version of MQTT");
            break;
        case 2:
            Serial.println("the server rejected the client identifier");
            break;
        case 3:
            Serial.println("the server was unable to accept the connection");
            break;
        case 4:
            Serial.println("the username/password were rejected");
            break;
        case 5:
            Serial.println("the client was not authorized to connect");
            break;
        }
        Serial.println("trynig to reconnect MQTT-client...");
        MQTTWasDisconnected = true;
        return false;
    }
}