#include "FWHandler.h"

FWHandlerClass::FWHandlerClass(WiFlyUDPClass *wiflyudp, RegistrarClass *registrar): wiflyudp_(wiflyudp), registrar_(registrar) {
    rindex_ = 0;
}

void FWHandlerClass::handle(const Vector &v) {
    AddressClass addr = AddressClass(v.packet.origin, v.source);
    bool address_handled = handled(addr);
    bool match_localhost = addr.matchEndpoint(MMT_DEF_ENDPOINT);
    bool smaller = rindex_ < AROS_MAX_REMOTES;
    if (!address_handled && !match_localhost && smaller) {
        raddr_[rindex_] = addr;
        IPAddress ip = IPAddress(addr.endpoint[0], addr.endpoint[1], addr.endpoint[2], addr.endpoint[3]);
        rbuf_[rindex_] = RemoteHandlerClass(wiflyudp_, ip);
        registrar_->registerSubscriber((const AddressClass)addr, &(rbuf_[rindex_]));
        rindex_++;
    }
}

bool FWHandlerClass::handled(const AddressClass &addr) {
    for (int i = 0; i < rindex_ ; i++) {
        AddressClass qaddr = raddr_[i];
        if ((AddressClass)addr == qaddr) {
            return true;
        }
    }
}
