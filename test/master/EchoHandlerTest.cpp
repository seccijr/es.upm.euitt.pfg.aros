#include "EchoHandlerTest.h"
#include "mock/FakeEchoCaptureHandler.h"
#include <EchoHandler.h>

void EchoHandlerTest::testEchoed() {
    // Arrange
    FakeEchoCaptureHandlerClass fake_handler;
    Address dst = {
        MMT_DEF_RESOURCE,
        {1, 0, 0, 127}
    };
    Direction incoming = {
        dst,
        Localhost
    };
    Direction outgoing = {
        Localhost,
        dst
    };
    Registrar.registerSubscriber(incoming, &EchoHandler);
    Registrar.registerSubscriber(outgoing, &fake_handler);
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
    assertTrue(fake_handler.called);
    char *match = strstr("HOLA", fake_handler.msg);
    assertTrue(match != NULL);
}

void EchoHandlerTest::setup() {
}

void EchoHandlerTest::once() {
    testEchoed();
}
