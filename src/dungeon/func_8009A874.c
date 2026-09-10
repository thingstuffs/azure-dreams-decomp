#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Finds the first neighboring direction with a negative probe result. */
s32 func_8009FFD4(u8 *entity, s16 *direction) {
    s32 neighbor = 0;
    s32 found;
    u16 *y_offset = D_8006CCE8;
    u16 *x_offset = D_8006CCD8;
    do {
        s16 probe_result;

        probe_result = func_8009FB34((entity[0x24] + *x_offset) & 0xFFFF, (entity[0x25] + *y_offset) & 0xFFFF);
        do {
        } while (0);
        y_offset++;
        if (probe_result >= 0) {
            goto next;
        }
        *direction = neighbor << 9;
        found = 1;
        goto done;
next:
        neighbor++;
        x_offset++;
    } while (neighbor < 8);
    found = 0;
done:
    return found;
}
