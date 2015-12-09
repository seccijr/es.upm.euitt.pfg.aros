#include "RemoteHandler.h"
#include "utility/aros_definitions.h"
#include <Wire.h>
#include <Master.h>

RemoteHandlerClass::RemoteHandlerClass() {
    wire_ = &Wire;
}

RemoteHandlerClass::RemoteHandlerClass(TwoWire *wire): wire_(wire) {}

void RemoteHandlerClass::handle(const Vector &v) {
    wire_->beginTransmission(AROS_COMM_WIRE_ADD);
    VectorSerializer::serialize(v, wire_);
    wire_->endTransmission();
}

RemoteHandlerClass RemoteHandler(&Wire);
