#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include "EchoHandler.h"
#include "FWHandler.h"
#include "utility/credentials.h"
#include "utility/aros_definitions.h"

void setup() {
    Serial.begin(9600);
    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(commVector);
    Registrar.registerSubscriber(Wildcard, &FWHandler);
    Registrar.registerSubscriber(Localhost, &EchoHandler);
}

void loop() {
    Registrar.flushQueue();
    delay(1000);
}

void commVector(int n) {
    if (n == MMT_VECTOR_LEN) {
        Vector v;
        VectorSerializer::deserialize(&v, &Wire);
        Registrar.publish(v);
    }
}
