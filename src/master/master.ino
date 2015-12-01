#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include "utility/VectorSerializer.h"
#include "utility/credentials.h"
#include "utility/aros_definitions.h"
#include "utility/aros_types.h"

void setup() {
    pinMode(13, OUTPUT);

    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(commVector);
    Serial.begin(9600);
}

void loop() {
}

void commVector(int n) {
    if (n == AROS_VECTOR_LEN) {
        byte buffer[AROS_VECTOR_LEN] = {0};
        int i = 0;
        while (Wire.available() > 0) {
            buffer[i++] = Wire.read();
        }
        Vector v;
        VectorSerializer::deserialize(&v, (const byte *)buffer);
        Serial.print("Source endpoint: ");
        Serial.print(v.source[0]);
        Serial.print(v.source[1]);
        Serial.print(v.source[2]);
        Serial.println(v.source[3]);
        Serial.print("Destination endpoint: ");
        Serial.print(v.destination[0]);
        Serial.print(v.destination[1]);
        Serial.print(v.destination[2]);
        Serial.println(v.destination[3]);
        Serial.print("Origin resource: ");
        Serial.print(v.packet.origin);
        Serial.println();
        Serial.print("Target resource: ");
        Serial.print(v.packet.target);
        Serial.println();
        Serial.print("Method: ");
        Serial.print(v.packet.method);
        Serial.println();
        Serial.print("Value: ");
        Serial.print(v.packet.message.value.l);
        Serial.println();
        Serial.println();
    }
}
