#ifndef TOWN_DEVKIT_LIST_METHODS_DATA_H
#define TOWN_DEVKIT_LIST_METHODS_DATA_H

#include "common.h"

/* Devkit list owner: callbacks at +0x68 and +0x74. */
typedef struct {
    u8 pad68[0x68];
    void (*func68)(void *, void *, s32);
    u8 pad6C[8];
    void (*func74)(s32);
} DevkitListMethods;

extern DevkitListMethods *devkit_list_methods[3];

#endif
