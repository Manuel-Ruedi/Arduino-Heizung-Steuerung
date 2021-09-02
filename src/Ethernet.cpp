#include <common.h>

// assign a MAC address for the ethernet controller.
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// for manual configuration:
IPAddress ip(192, 168, 0, 147);
// initialize the library instance:
EthernetClient Ethernetclient;

bool EthernetWasDisconnected = false;
extern bool MQTTWasDisconnected;

bool checkEthernet(); // return true if connection is ok else false

bool Ethernetinit()
{
    Serial.print("initializing Ethernet...");
    Ethernet.init(10); // init to pin 10

    if (Ethernet.begin(mac) == 0) // start the Ethernet connection:
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        Serial.println("using static IP: 192.168.0.147");
        // DHCP failed, so use a fixed IP address:
        Ethernet.begin(mac, ip);
    }
    delay(1000);
    if (checkEthernet())
    {
        Serial.println("successful");
        Serial.print("IP: ");
        Serial.println(Ethernet.localIP());
        return true;
    }
    else
        return false;
}

bool Ethernetloop()
{
    if (checkEthernet())
    {
        Ethernet.maintain(); //renewal of DHCP leases if nessesary.
        return true;
    }
    else
        return false;
}

bool checkEthernet()
{
    if (Ethernet.linkStatus() == LinkON)
    {
        if (EthernetWasDisconnected)
        {
            Serial.println("Ethernet: reconnected!");
            Serial.print("IP: ");
            Serial.println(Ethernet.localIP());
            EthernetWasDisconnected = false;
        }
        return true;
    }
    else if (Ethernet.linkStatus() == LinkOFF)
    {
        if (!EthernetWasDisconnected)
        {
            Serial.println("Ethernet: no Link!");
            EthernetWasDisconnected = true;
            MQTTWasDisconnected = true;
        }
        return false;
    }
    else if (Ethernet.linkStatus() == Unknown)
    {
        Serial.println("Ethernet Link status unknown. Link status detection is only available with W5200 and W5500.");
        return false;
    }
    return false;
}