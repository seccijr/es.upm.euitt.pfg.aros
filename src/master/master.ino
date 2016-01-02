#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include <ArduinoRobot.h>
#include "TokenCollectorHandler.h"
#include "FWHandler.h"
#include "utility/credentials.h"
#include "utility/aros_definitions.h"

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    Robot.beginSpeaker();
    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(commVector);
    Registrar.registerSubscriber(Wildcard, &FWHandler);
    Registrar.registerSubscriber(Localhost, &TokenCollectorHandler);
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
