#ifndef _REMOTEHANDLER_H
#define _REMOTEHANDLER_H

#include <Wire.h>
#include <Master.h>

class RemoteHandlerClass: public EventHandler {
    public:
        RemoteHandlerClass();
        RemoteHandlerClass(TwoWire *wire);
        void handle(const Vector &v);
    private:
        TwoWire *wire_;
};

extern RemoteHandlerClass RemoteHandler;

#endif
