#ifndef _FWHANDLER_H
#define _FWHANDLER_H

#include <Comm.h>
#include <Master.h>
#include "RemoteHandler.h"
#include "utility/aros_definitions.h"

class FWHandlerClass: public EventHandler {
    public:
        FWHandlerClass(WiFlyUDPClass *wiflyudp, RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool handled(const AddressClass &addr);
        WiFlyUDPClass *wiflyudp_;
        RegistrarClass *registrar_;
        RemoteHandlerClass rbuf_[AROS_MAX_REMOTES];
        AddressClass raddr_[AROS_MAX_REMOTES];
        int rindex_;
};

extern FWHandlerClass FWHandler;

#endif
