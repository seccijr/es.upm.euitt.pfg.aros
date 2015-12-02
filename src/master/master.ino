#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include "EchoHandler.h"
#include "utility/credentials.h"
#include "utility/aros_definitions.h"

void setup() {
    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(commVector);
    Serial.begin(9600);
    Registrar.registerSubscriber(Localhost, &EchoHandler);
}

void loop() {
    Registrar.flushQueue();
}

void commVector(int n) {
    if (n == MMT_VECTOR_LEN) {
        byte buffer[MMT_VECTOR_LEN] = {0};
        int i = 0;
        while (Wire.available() > 0) {
            buffer[i++] = Wire.read();
        }
        Vector v;
        VectorSerializer::deserialize(&v, (const byte *)buffer);
        Registrar.publish(v);
    }
}
