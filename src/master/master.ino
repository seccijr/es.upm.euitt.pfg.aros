#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include "credentials.h"
#include "aros_definitions.h"

void setup() {
    pinMode(13, OUTPUT);

    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(receiveEvent);
    Serial.begin(9600);
}

void loop() {
}

void receiveEvent(int howMany) {
    while (1 < Wire.available()) {
        char c = Wire.read();
        Serial.print(c);
    }
    char last = Wire.read();
    Serial.println(last);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
