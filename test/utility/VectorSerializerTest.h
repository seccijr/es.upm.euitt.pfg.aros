#ifndef _VECTORSERIALIZERTEST_H
#define _VECTORSERIALIZERTEST_H

#include <Arduino.h>
#include <ArduinoUnit.h>

class VectorSerializerTest: public TestOnce {
    public:
        VectorSerializerTest(const char *name): TestOnce(name) {
            verbosity = TEST_VERBOSITY_ALL;
        }
        void setup();
        void once();
    private:
        void TestDeserialize();
};

#endif
