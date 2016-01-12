#ifndef _CARRIERHANDLER_H
#define _CARRIERHANDLER_H

#include <Master.h>
#include <Servo.h>

class CarrierHandlerClass: public EventHandler {
    public:
        CarrierHandlerClass(RegistrarClass *registrar);
        void handle(const Vector &v);
    private:
        bool waitForResponse(const long code, const long timeout);
        bool meetingPoint();
        bool backHome();
        bool answer(const unsigned long msg);
        RegistrarClass *registrar_;
};

extern CarrierHandlerClass CarrierHandler;

#endif
