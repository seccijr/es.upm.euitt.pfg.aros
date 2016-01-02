#include "TokenCollectorHandler.h"
#include <Master.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>
#include "utility/aros_definitions.h"

#define COLLECTOR_TIMEOUT 30000


TokenCollectorHandlerClass::TokenCollectorHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {

    }

void TokenCollectorHandlerClass::handle(const Vector &v) {
    Robot.beep(BEEP_DOUBLE);
    Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
    bool result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, COLLECTOR_TIMEOUT);
    if (result) {
        Serial1.write(MOTOR_COMMAND_TURN_ARROUND);
        result = waitForResponse(MOTOR_COMMAND_TURN_ARROUND_END, COLLECTOR_TIMEOUT);
    }
    if (result) {
        Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
        result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, COLLECTOR_TIMEOUT);
    }
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
    Robot.beep(BEEP_LONG);
}

bool TokenCollectorHandlerClass::waitForResponse(const long code, const long timeout) {
    long start = millis();
    bool success = false, exceeded = false, connected = false;
    do {
        if (Serial1.available() > 0) {
            byte msg = Serial1.read();
            success = msg == code;
            connected = true;
        }
        exceeded = (millis() - start) > timeout;
    } while (!connected && !exceeded);
    return success;
}

TokenCollectorHandlerClass TokenCollectorHandler(&Registrar);
