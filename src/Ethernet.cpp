#include <common.h>

// initialize the library instance:
EthernetClient Ethernetclient;

// assign a MAC address for the ethernet controller.
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// for manual configuration:
IPAddress ip(192, 168, 0, 147);

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
        switch (Ethernet.maintain()) // renewal of DHCP leases if nessesary.
        {
        case 0: // nothing happened
            return true;
            break;
        case 1:
            Serial.println("DHCP: renew failed");
            return false;
            break;
        case 2: // DHCP: renew success
            return true;
            break;
        case 3:
            Serial.println("DHCP: rebind fail");
            return false;
            break;
        case 4: // rebind success
            return true;
            break;
        default:
            break;
        }
        return true;
    }
    else
        return false;
}

bool checkEthernet()
{
    if ((Ethernet.linkStatus() == LinkON) & (Ethernet.localIP() != IPAddress(0, 0, 0, 0)))
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
    else if ((Ethernet.linkStatus() == LinkOFF) | (Ethernet.localIP() == IPAddress(0, 0, 0, 0)))
    {
        if (!EthernetWasDisconnected)
        {
            Serial.println("Ethernet: no Link!");
            EthernetWasDisconnected = true;
            if (Ethernet.localIP() == IPAddress(0, 0, 0, 0))
            {
                Serial.println("error check cable to ethernet device!");
                Serial.println("Then restart.");
            }
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