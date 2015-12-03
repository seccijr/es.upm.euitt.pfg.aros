#ifndef _ECHOHANDLETTEST_H
#define _ECHOHANDLETTEST_H

#include <Arduino.h>
#include <ArduinoUnit.h>
#include <EchoHandler.h>

class EchoHandlerTest: public TestOnce {
    public:
        EchoHandlerTest(const char *name): TestOnce(name) {
            verbosity = TEST_VERBOSITY_ALL;
        }
        void setup();
        void once();
    private:
        void testEchoed();
};

#endif
