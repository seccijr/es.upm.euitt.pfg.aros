#include "VectorSerializerTest.h"
#include "utility/aros_types.h"
#include "utility/aros_definitions.h"
#include "utility/VectorSerializer.h"
#include <Master.h>

void VectorSerializerTest::TestDeserialize() {
    const byte buffer[AROS_VECTOR_LEN] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07,0x08,
        0x09, 0x0A, MMT_GET, MMT_STR,
        'H', 'O', 'L', 'A'
    };
    Vector v;
    VectorSerializer::deserialize(&v, buffer);
    for (int i = 0; i < 4; i++) {
        assertTrue(v.source[i] == buffer[i]);
    }
    for (int i = 0; i < 4; i++) {
        assertTrue(v.destination[i] == buffer[i + 4]);
    }
    assertTrue(v.packet.origin == buffer[8]);
    assertTrue(v.packet.target == buffer[9]);
    assertTrue(v.packet.method == buffer[10]);
    assertTrue(v.packet.message.type == buffer[11]);
    char hola[5] = {0};
    memcpy(hola, v.packet.message.value.b, 4);
    char *match = strstr(hola, "HOLA");
    assertTrue(match != NULL);
}

void VectorSerializerTest::setup() {
}

void VectorSerializerTest::once() {
    TestDeserialize();
}
