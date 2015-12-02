#include "EchoHandler.h"
#include <Master.h>

EchoHandlerClass::EchoHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {

    }

void EchoHandlerClass::handle(const Vector &v) {
    Packet epckt = v.packet;
    epckt.origin = v.packet.target;
    epckt.target = v.packet.origin;
    Vector ev;
    for (int i = 0; i < MMT_ENDPOINT_LEN; i++) {
        ev.destination[i] = v.source[i];
        ev.source[i] = v.destination[i];
    }
    ev.packet = epckt;
    registrar_->publish((const Vector)ev);
}

EchoHandlerClass EchoHandler(&Registrar);
