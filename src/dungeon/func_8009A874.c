#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Finds the first neighboring direction with a negative probe result. */
s32 func_8009FFD4(u8 *entity, s16 *direction) {
    s32 neighbor;

    for (neighbor = 0; neighbor < 8; neighbor++) {
        if (func_8009FB34((entity[0x24] + D_8006CCD8[neighbor]) & 0xFFFF,
                          (entity[0x25] + D_8006CCE8[neighbor]) & 0xFFFF) < 0) {
            *direction = neighbor << 9;
            return 1;
        }
    }
    return 0;
}
