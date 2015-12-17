#ifndef _PIROUETTEHANDLER_H
#define _PIROUETTEHANDLER_H

#include <Master.h>

class PirouetteHandlerClass: public EventHandler {
    public:
        PirouetteHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        RegistrarClass *registrar_;
};

extern PirouetteHandlerClass PirouetteHandler;

#endif
