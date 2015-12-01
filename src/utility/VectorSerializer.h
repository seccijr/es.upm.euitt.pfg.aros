#ifndef _VECTORSERIALIZER_H
#define _VECTORSERIALIZER_H

#include <Master.h>
#include "utility/aros_types.h"

class VectorSerializer {
    public:
        static void deserialize(Vector *vector, const byte *buffer);
        static void serialize(const AddressClass &source, const AddressClass &destination, const Packet &packet, Print &p);
};

#endif
