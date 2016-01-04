#ifndef _TOKENCOLLECTORHANDLER_H
#define _TOKENCOLLECTORHANDLER_H

#include <Master.h>
#include <Servo.h>

class TokenCollectorHandlerClass: public EventHandler {
    public:
        TokenCollectorHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool waitForResponse(const long code, const long timeout);
        bool collect();
        bool dispose();
        void openArm();
        void closeArm();
        Servo arm_;
        RegistrarClass *registrar_;
};

extern TokenCollectorHandlerClass TokenCollectorHandler;

#endif
