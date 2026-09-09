#include "common.h"

extern u8 D_800E045D[];

/* Append two table bytes followed by two bytes of value 7. */
void *func_80099978(void *buffer) {
    u8 *dst = (u8 *)buffer;

    *dst = D_800E045D[0];
    dst++;
    *dst = D_800E045D[1];
    do {
        dst++;
    } while (0);
    *dst = 7;
    dst++;
    *dst = 7;
    dst++;

    return dst;
}
