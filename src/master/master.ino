#include <Arduino.h>
#include <Wire.h>
#include <Master.h>
#include "TokenCollectorHandler.h"
#include "CarrierHandler.h"
#include "FWHandler.h"
#include "RemoteHandler.h"
#include "utility/credentials.h"
#include "utility/aros_definitions.h"
#include "utility/rol.h"

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    Wire.begin(AROS_MASTER_WIRE_ADD);
    Wire.onReceive(commVector);
    Registrar.registerSubscriber(Wildcard, &FWHandler);
    Registrar.registerSubscriber(Netcast, &RemoteHandler);
#if defined(AROS_ROL_COLLECTOR)
    Registrar.registerSubscriber(Localhost, &TokenCollectorHandler);
#elif defined(AROS_ROL_CARRIER)
    Registrar.registerSubscriber(Localhost, &CarrierHandler);
#endif
}

void loop() {
    Registrar.flushQueue();
    delay(1000);
}

void commVector(int n) {
    if (n == MMT_VECTOR_LEN) {
        Vector v;
        VectorSerializer::deserialize(&v, &Wire);
        Registrar.publish(v);
    }
}
