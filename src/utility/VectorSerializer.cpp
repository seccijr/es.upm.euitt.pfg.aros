#include "VectorSerializer.h"
#include <Master.h>

void VectorSerializer::deserialize(Vector *vector, const byte *buffer) {
    memcpy(vector->source, buffer, MMT_ENDPOINT_LEN);
    memcpy(vector->destination, buffer + MMT_ENDPOINT_LEN, MMT_ENDPOINT_LEN);
    Packet pckt;
    PacketSerializer::deserialize(&pckt, buffer + (2 * MMT_ENDPOINT_LEN));
    vector->packet = pckt;
}

void VectorSerializer::serialize(const AddressClass &source, const AddressClass &destination, const Packet &packet, Print &p) {
    for (int i = 0; i < 4; i++) {
        p.write(source.endpoint[i]);
    }
    for (int i = 0; i < 4; i++) {
        p.write(destination.endpoint[i]);
    }
    PacketSerializer::serialize(packet, p);
}
