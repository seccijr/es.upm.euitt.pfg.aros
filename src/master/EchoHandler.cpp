#include "EchoHandler.h"
#include <Master.h>

EchoHandlerClass::EchoHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {

    }

void EchoHandlerClass::handle(const Vector &v) {
    Direction backward = {
        v.direction.destination,
        v.direction.source
    };
    Vector ev = {
        v.packet,
        backward
    };
    registrar_->publish((const Vector)ev);
}

EchoHandlerClass EchoHandler(&Registrar);
