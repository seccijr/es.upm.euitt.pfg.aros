#ifndef _FAKEECHOCAPTUREHANDLER_H
#define _FAKEECHOCAPTUREHANDLER_H

#include <Master.h>

class FakeEchoCaptureHandlerClass: public EventHandler {
    public:
        FakeEchoCaptureHandlerClass() {
            memset(msg, 0, 5);
        };
        void handle(const Vector &v) {
            called = true;
            memcpy(msg, v.packet.message.value.b, 4);
        };
        bool called = false;
        char msg[5];
};

#endif
