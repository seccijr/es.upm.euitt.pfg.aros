#ifndef _REMOTEHANDLER_H
#define _REMOTEHANDLER_H

#include <Comm.h>
#include <Master.h>
#include <IPAddress.h>

class RemoteHandlerClass: public EventHandler {
    public:
        RemoteHandlerClass();
        RemoteHandlerClass(WiFlyUDPClass *wiflyudp, IPAddress dest);
        void handle(const Vector &v);
    private:
        WiFlyUDPClass *wiflyudp_;
        IPAddress destination_;
};

#endif
