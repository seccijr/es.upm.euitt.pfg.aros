#ifndef _FWHANDLER_H
#define _FWHANDLER_H

#include <Wire.h>
#include <Master.h>
#include "RemoteHandler.h"
#include "utility/aros_definitions.h"

class FWHandlerClass: public EventHandler {
    public:
        FWHandlerClass(TwoWire *wire, RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool handled(const AddressClass &addr);
        TwoWire *wire_;
        RegistrarClass *registrar_;
        RemoteHandlerClass rbuf_[AROS_MAX_REMOTES];
        AddressClass raddr_[AROS_MAX_REMOTES];
        int rindex_;
};

extern FWHandlerClass FWHandler;

#endif
