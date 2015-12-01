#include <Arduino.h>
#include <Wire.h>
#include <IPAddress.h>
#include <Comm.h>
#include <Master.h>
#include "utility/credentials.h"
#include "utility/aros_definitions.h"
#include "utility/VectorSerializer.h"

char buffer[MMT_PACKET_LEN] = {0};

void setup() {
    Serial.begin(9600);
    Wire.begin(AROS_COMM_WIRE_ADD);
    WiFlyWiFi.begin((char *)OPEN_SSID);
    WiFlyUDP.begin(2000);
}

void loop() {
    int n = WiFlyUDP.read(buffer, MMT_PACKET_LEN, 10);
    if (n == MMT_PACKET_LEN) {
        commPacket((const byte *)buffer);
        memset(buffer, 0, MMT_PACKET_LEN);
    }
}

void commPacket(const byte *buffer) {
    IPAddress ip = WiFlyUDP.remoteIP();
    AddressClass source = AddressClass(ip[0], ip[1], ip[2], ip[3]);
    Packet pckt = {0};
    PacketSerializer::deserialize(&pckt, buffer);
    Wire.beginTransmission(AROS_MASTER_WIRE_ADD);
    VectorSerializer::serialize((const AddressClass)source, (const AddressClass)Localhost, (const Packet)pckt, Wire);
    Wire.endTransmission();
}
