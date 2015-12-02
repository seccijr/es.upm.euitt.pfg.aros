#ifndef _REMOTEHANDLER_H
#define _REMOTEHANDLER_H

#include <Comm.h>
#include <Master.h>
#include <IPAddress.h>

class RemoteHandlerClass: public EventHandler {
    public:
        RemoteHandlerClass(WiFlyUDPClass *wiflyudp, RegistrarClass *registrar, IPAddress dest);
        void handle(const Vector &v);
    private:
        WiFlyUDPClass *wiflyudp_;
        RegistrarClass *registrar_;
        IPAddress destination_;
};

extern RemoteHandlerClass RemoteHandler;

#endif
