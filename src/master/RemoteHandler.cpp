#include "RemoteHandler.h"
#include "utility/aros_definitions.h"
#include <Comm.h>
#include <Master.h>
#include <IPAddress.h>

RemoteHandlerClass::RemoteHandlerClass() {
    wiflyudp_ = &WiFlyUDP;
    destination_ = IPAddress();
}

RemoteHandlerClass::RemoteHandlerClass(WiFlyUDPClass *wiflyudp, IPAddress dest):
    wiflyudp_(wiflyudp), destination_(dest) {

    }

void RemoteHandlerClass::handle(const Vector &v) {
    wiflyudp_->beginPacket(destination_, AROS_DEFAULT_PORT);
    PacketSerializer::serialize(v.packet, wiflyudp_);
    wiflyudp_->endPacket();
}
