#ifndef _FWHANDLERTEST_H
#define _FWHANDLERTEST_H

#include <Arduino.h>
#include <ArduinoUnit.h>

class FWHandlerTest: public TestOnce {
    public:
        FWHandlerTest(const char *name): TestOnce(name) {
            verbosity = TEST_VERBOSITY_ALL;
        }
        void setup();
        void once();
    private:
        void testFiltered();
};

#endif
