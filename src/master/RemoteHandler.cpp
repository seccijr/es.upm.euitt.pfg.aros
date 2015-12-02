#include "RemoteHandler.h"
#include "utility/aros_definitions.h"
#include <Comm.h>
#include <Master.h>
#include <IPAddress.h>

RemoteHandlerClass::RemoteHandlerClass(WiFlyUDPClass *wiflyudp, RegistrarClass *registrar, IPAddress dest):
    wiflyudp_(wiflyudp), registrar_(registrar), destination_(dest) {

    }

void RemoteHandlerClass::handle(const Vector &v) {
    wiflyudp_->beginPacket(destination_, AROS_DEFAULT_PORT);
    PacketSerializer::serialize(v.packet, wiflyudp_);
    wiflyudp_->endPacket();
}

RemoteHandlerClass RemoteHandler(&WiFlyUDP, &Registrar, IPAddress(255, 255, 255, 255));
