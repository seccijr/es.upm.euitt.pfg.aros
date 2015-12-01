#ifndef _AROSTYPE_H
#define _AROSTYPE_H

#include <Master.h>

typedef struct {
    Packet packet;
    byte source[MMT_ENDPOINT_LEN];
    byte destination[MMT_ENDPOINT_LEN];
} Vector;

#endif
