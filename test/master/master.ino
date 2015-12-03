#include <Arduino.h>
#include <ArduinoUnit.h>

EchoHandlerTest echo_test = EchoHandlerTest("EchoHandler");

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        ;
    }
}

void loop() {
    Test::run();
}
