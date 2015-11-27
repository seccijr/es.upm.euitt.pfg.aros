#include <Arduino.h>
#include <Wire.h>
#include <IPAddress.h>
#include <Comm.h>
#include "credentials.h"
#include "aros_definitions.h"

char buffer[AROS_MAX_PACKET_LEN +  1] = {0};

void setup() {
    Serial.begin(9600);
    Wire.begin(AROS_COMM_WIRE_ADD);
    WiFlyWiFi.begin((char *)OPEN_SSID);
    WiFlyUDP.begin(2000);
}

void loop() {
    int result = WiFlyUDP.read(buffer, AROS_MAX_PACKET_LEN, 10);
    if (result > 0) {
        Wire.beginTransmission(AROS_MASTER_WIRE_ADD);
        Wire.write(buffer);
        Wire.endTransmission();
    }
    memset(buffer, 0, AROS_MAX_PACKET_LEN);
}
