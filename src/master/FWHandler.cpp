#include "FWHandler.h"

FWHandlerClass::FWHandlerClass(RegistrarClass *registrar): registrar_(registrar) {
    rindex_ = 0;
}

void FWHandlerClass::handle(const Vector &v) {
    Address source = v.direction.source;
    bool address_handled = handled(source);
    bool match_localhost = source.matchEndpoint(MMT_DEF_ENDPOINT);
    bool smaller = rindex_ < AROS_MAX_REMOTES;
    if (!address_handled && !match_localhost && smaller) {
        raddr_[rindex_++] = source;
        Direction backward = {
            v.direction.destination,
            source
        };
        registrar_->registerSubscriber(backward, &RemoteHandler);
    }
}

bool FWHandlerClass::handled(const Address &addr) {
    for (int i = 0; i < rindex_ ; i++) {
        Address qaddr = raddr_[i];
        if ((Address)addr == qaddr) {
            return true;
        }
    }
    return false;
}

FWHandlerClass FWHandler(&Registrar);
