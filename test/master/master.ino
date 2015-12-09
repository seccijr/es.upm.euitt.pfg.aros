#include <Arduino.h>
#include <ArduinoUnit.h>
#include "EchoHandlerTest.h"
#include "FWHandlerTest.h"

EchoHandlerTest echo_test = EchoHandlerTest("EchoHandler");
FWHandlerTest fw_test = FWHandlerTest("FWHandler");

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        ;
    }
}

void loop() {
    Test::run();
}
