#ifndef _ECHOHANDLER_H
#define _ECHOHANDLER_H

#include <Master.h>

class EchoHandlerClass: public EventHandler {
    public:
        EchoHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        RegistrarClass *registrar_;
};

extern EchoHandlerClass EchoHandler;

#endif
