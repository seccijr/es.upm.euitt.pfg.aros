#include <Arduino.h>
#include "utility/credentials.h"
#include "utility/aros_definitions.h"

void setup() {
    Serial1.begin(9600);
}

void loop() {
    int n = Serial1.available();
    if (n == MMT_VECTOR_LEN) {
        masterVector(n);
    }
    delay(1000);
}

void masterVector(int n) {
    Packet pckt;
    PacketSerializer::deserialize(&pckt, &Serial1);
    masterSelector(pckt);
}

void masterSelector(const Packet &pckt) {
    switch (pckt.message.value) {
        case MOTOR_COMMAND_LINE_FOLLOW:
            break;
        case MOTOR_COMMAND_TURN_ARROUND:
            break;
        default:
            break;
    }
}
