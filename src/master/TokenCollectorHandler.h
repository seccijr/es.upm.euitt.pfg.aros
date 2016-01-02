#ifndef _TOKENCOLLECTORHANDLER_H
#define _TOKENCOLLECTORHANDLER_H

#include <Master.h>

class TokenCollectorHandlerClass: public EventHandler {
    public:
        TokenCollectorHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool waitForResponse(const long code, const long timeout);
        RegistrarClass *registrar_;
};

extern TokenCollectorHandlerClass TokenCollectorHandler;

#endif
