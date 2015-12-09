#ifndef _FAKEWIRE_H
#define _FAKEWIRE_H

#include <Wire.h>

class FakeWire: public TwoWire {
    public:
        FakeWire() {
            index = 0;
            written = false;
        };
        size_t write(byte b) {
            if (index < MMT_VECTOR_LEN) {
                written_buffer[index++] = b;
                return 1;
            }
            return 0;
        };
        size_t write(byte *buffer, size_t len) {
            int result = 0;
            if (index + len <= MMT_VECTOR_LEN) {
                for (int i = 0; i < len; i++) {
                    result += write(buffer[i]);
                }
            }
            return result;
        };
        int read(void) {
            if (index > 0) {
                --index;
                return written_buffer[index];
            }
            return -1;
        };
        byte written_buffer[MMT_VECTOR_LEN];
        int index;
        bool written;
};

#endif
