#include "TokenCollectorHandler.h"
#include "utility/aros_definitions.h"

#define COLLECTOR_TIMEOUT 30000


TokenCollectorHandlerClass::TokenCollectorHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {
    }

void TokenCollectorHandlerClass::handle(const Vector &v) {
    Message message;
    message.type = MMT_LONG;
    switch (v.packet.message.value.l) {
        case AROS_TOKEN_CMD:
            collect();
            answer(AROS_TOKEN_POS);
            break;
        case AROS_TOKEN_REL:
            openArm();
            answer(AROS_TOKEN_FRE);
            break;
        case AROS_TRANSPORT_END:
            dispose();
            answer(AROS_TOKEN_END);
            break;
        default:
            break;
    }
}

bool TokenCollectorHandlerClass::answer(const unsigned long msg) {
    Message message;
    message.type = MMT_LONG;
    message.value.l = msg;
    Packet packet = {
        MMT_POST,
        message
    };
    Address net_all = {
        MMT_DEF_RESOURCE,
        {255, 255, 255, 255}
    };
    Direction backward = {
        Localhost,
        net_all
    };
    Vector ev = {
        packet,
        backward
    };
    registrar_->publish((const Vector)ev);
}

bool TokenCollectorHandlerClass::collect() {
    openArm();
    Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
    bool result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, COLLECTOR_TIMEOUT);
    if (result) {
        closeArm();
    }
    if (result) {
        Serial1.write(MOTOR_COMMAND_TURN_ARROUND);
        result = waitForResponse(MOTOR_COMMAND_TURN_ARROUND_END, COLLECTOR_TIMEOUT);
    }
    if (result) {
        Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
        result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, COLLECTOR_TIMEOUT);
    }
    return result;
}

bool TokenCollectorHandlerClass::dispose() {
    Serial1.write(MOTOR_COMMAND_TURN_ARROUND);
    bool result = waitForResponse(MOTOR_COMMAND_TURN_ARROUND_END, COLLECTOR_TIMEOUT);
    if (result) {
        closeArm();
    }
    return result;
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

void TokenCollectorHandlerClass::openArm() {
    arm_.attach(TKD4);
    for (int pos = 70; pos <= 180; pos += 1) {
        arm_.write(pos);
        delay(15);
    }
    arm_.detach();
}

void TokenCollectorHandlerClass::closeArm() {
    arm_.attach(TKD4);
    for (int pos = 180; pos >= 70; pos -= 1) {
        arm_.write(pos);
        delay(15);
    }
    arm_.detach();
}

TokenCollectorHandlerClass TokenCollectorHandler(&Registrar);
