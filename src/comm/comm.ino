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
    WiFlyWiFi.begin((char *)SECURED_SSID, (char *)SECURED_PASS);
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
    Address source = {
        buffer[0],
        {ip[0], ip[1], ip[2], ip[3]}
    };
    Address destination = {
        buffer[1],
        {127, 0, 0, 1}
    };
    Packet pckt;
    PacketSerializer::deserialize(&pckt, buffer + 2);
    Direction drct = {
        source,
        destination
    };
    Vector v = {
        pckt,
        drct
    };
    Wire.beginTransmission(AROS_MASTER_WIRE_ADD);
    VectorSerializer::serialize(v, &Wire);
    Wire.endTransmission();
}

void masterVector(int n) {
    if (n == MMT_VECTOR_LEN) {
        Vector v;
        VectorSerializer::deserialize(&v, &Wire);
        IPAddress ip(v.direction.destination.endpoint[0], v.direction.destination.endpoint[1], v.direction.destination.endpoint[2], v.direction.destination.endpoint[3]);
        WiFlyUDP.beginPacket(ip, AROS_DEFAULT_PORT);
        WiFlyUDP.write(v.direction.source.resource);
        WiFlyUDP.write(v.direction.destination.resource);
        PacketSerializer::serialize((const Packet)v.packet, &WiFlyUDP);
        WiFlyUDP.endPacket();
    }
}
