#ifndef TOWN_DEVKIT_RUNTIME_CALLBACK_OWNER_DATA_H
#define TOWN_DEVKIT_RUNTIME_CALLBACK_OWNER_DATA_H

#include "common.h"

/* Callback owner in the 0x80700000-linked town devkit image. */
typedef struct {
    u8 pad60[0x60];
    void (*invoke)(s32 code);
    u8 pad64[4];
    void (*func68)(void *, void *, s32);
    u8 pad6C[8];
    void (*func74)(s32);
} DevkitRuntimeCallbacks;

extern DevkitRuntimeCallbacks *devkit_runtime_callback_owner[3];

#endif
