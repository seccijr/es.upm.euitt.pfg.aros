#include <Arduino.h>
#include <ArduinoUnit.h>
#include "VectorSerializerTest.h"

VectorSerializerTest test = VectorSerializerTest("VectorSerializer");

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        ;
    }
}

void loop() {
    Test::run();
}
