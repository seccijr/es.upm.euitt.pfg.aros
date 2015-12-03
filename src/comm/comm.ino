#include <Arduino.h>
#include <Wire.h>
#include <IPAddress.h>
#include <Comm.h>
#include <Master.h>
#include "utility/credentials.h"
#include "utility/aros_definitions.h"

char buffer[MMT_PACKET_LEN] = {0};

void setup() {
    Serial.begin(9600);
    Wire.begin(AROS_COMM_WIRE_ADD);
    Wire.onReceive(masterVector);
    WiFlyWiFi.begin((char *)OPEN_SSID);
    WiFlyUDP.begin(AROS_DEFAULT_PORT);
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
    AddressClass destination = AddressClass((byte)127, (byte)0, (byte)0, (byte)1);
    Packet pckt = {0};
    PacketSerializer::deserialize(&pckt, buffer);
    Wire.beginTransmission(AROS_MASTER_WIRE_ADD);
    VectorSerializer::serialize((const AddressClass)source, (const AddressClass)destination, (const Packet)pckt, Wire);
    Wire.endTransmission();
}

void masterVector(int n) {
    if (n == MMT_VECTOR_LEN) {
        Vector v;
        VectorSerializer::deserialize(&v, &Wire);
        IPAddress ip(v.destination[0], v.destination[1], v.destination[2], v.destination[3]);
        WiFlyUDP.beginPacket(ip, AROS_DEFAULT_PORT);
        PacketSerializer::serialize((const Packet)v.packet, &WiFlyUDP);
        WiFlyUDP.endPacket();
    }
}
