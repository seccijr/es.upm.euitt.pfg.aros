#ifndef _FWHANDLER_H
#define _FWHANDLER_H

#include <Master.h>
#include "RemoteHandler.h"
#include "utility/aros_definitions.h"

class FWHandlerClass: public EventHandler {
    public:
        FWHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool handled(const Address &addr);
        RegistrarClass *registrar_;
        Address raddr_[AROS_MAX_REMOTES];
        int rindex_;
};

extern FWHandlerClass FWHandler;

#endif
