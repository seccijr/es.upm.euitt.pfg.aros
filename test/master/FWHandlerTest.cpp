#include "FWHandlerTest.h"
#include "mock/FakeEchoCaptureHandler.h"
#include "mock/FakeWire.h"
#include <FWHandler.h>
#include <EchoHandler.h>

void FWHandlerTest::testFiltered() {
    // Arrange
    Wire.begin(AROS_MASTER_WIRE_ADD);
    Direction incoming = {
        Broadcast,
        Localhost
    };
    Registrar.registerSubscriber(Wildcard, &FWHandler);
    Registrar.registerSubscriber(Localhost, &EchoHandler);
    Message msg;
    msg.type = MMT_STR;
    memcpy(msg.value.b, "HOLA", 4);
    Packet pckt = {
        MMT_POST,
        msg
    };
    Vector v = {
        pckt,
        incoming
    };

    // Act
    Registrar.publish(v);
    Registrar.flushQueue();

    // Assert
}

void FWHandlerTest::setup() {
}

void FWHandlerTest::once() {
    testFiltered();
}
