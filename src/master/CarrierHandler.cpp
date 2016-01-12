#include "CarrierHandler.h"
#include "utility/aros_definitions.h"

#define CARRIER_TIMEOUT 30000


CarrierHandlerClass::CarrierHandlerClass(RegistrarClass *registrar):
    registrar_(registrar) {
    }

void CarrierHandlerClass::handle(const Vector &v) {
    switch (v.packet.message.value.l) {
        case AROS_TOKEN_POS:
            meetingPoint();
            answer(AROS_TOKEN_REL);
            break;
        case AROS_TOKEN_FRE:
            backHome();
            answer(AROS_TRANSPORT_END);
            break;
        default:
            break;
    }
}

bool CarrierHandlerClass::answer(const unsigned long msg) {
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

bool CarrierHandlerClass::meetingPoint() {
    Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
    bool result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, CARRIER_TIMEOUT);
    return result;
}

bool CarrierHandlerClass::backHome() {
    Serial1.write(MOTOR_COMMAND_TURN_ARROUND);
    bool result = waitForResponse(MOTOR_COMMAND_TURN_ARROUND_END, CARRIER_TIMEOUT);
    if (result) {
        Serial1.write(MOTOR_COMMAND_LINE_FOLLOW);
        result = waitForResponse(MOTOR_COMMAND_LINE_FOLLOW_END, CARRIER_TIMEOUT);
    }
    return result;
}

bool CarrierHandlerClass::waitForResponse(const long code, const long timeout) {
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

CarrierHandlerClass CarrierHandler(&Registrar);
