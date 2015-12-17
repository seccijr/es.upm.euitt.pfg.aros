#include "PirouetteHandler.h"
#include <Master.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>


PirouetteHandlerClass::PirouetteHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {

    }

void PirouetteHandlerClass::handle(const Vector &v) {
    Robot.begin();
    Robot.motorsWrite(255, 255);
    delay(2000);
    Robot.motorsStop();
    delay(1000);
    Robot.motorsWrite(-255, -255);
    delay(1000);
    Robot.motorsWrite(0, 0);
    delay(1000);
    Robot.motorsWrite(-255, 255);
    delay(2000);
    Robot.motorsStop();
    delay(1000);
    Robot.motorsWrite(255, -255);
    delay(2000);
    Robot.motorsStop();
    Message message = {
        MMT_STR
    };
    memcpy(message.value.b, "DONE", 4);
    Packet packet = {
        MMT_POST,
        message
    };
    Direction backward = {
        v.direction.destination,
        v.direction.source
    };
    Vector ev = {
        packet,
        backward
    };
    registrar_->publish((const Vector)ev);
}

PirouetteHandlerClass PirouetteHandler(&Registrar);
