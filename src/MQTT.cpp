#include <common.h>

extern EthernetClient Ethernetclient;
PubSubClient MQTTclient(Ethernetclient);

const char Devicename[] = "arduino-heizung";
const char Username[] = "MQTT-user";
const char Password[] = MQTTPASSWORD;

bool MQTTWasDisconnected = false;
bool checkMQTT();

bool MQTTconnect()
{
    return MQTTclient.connect(Devicename, Username, Password);
}

bool MQTTInit()
{
    Serial.print("Connecting MQTT-client...");
    MQTTclient.setServer("192.168.0.201", 1883);
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
    if (MQTTclient.state() == 0) //everything ok?
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