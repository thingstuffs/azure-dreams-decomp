#include "common.h"
#include "dungeon/item.h"

extern u8 D_800E045D[];

/* Append two table bytes followed by two bytes of value 7. */
void *append_value_seven_suffix(u8 *dst) {
    *dst++ = D_800E045D[0];
    *dst++ = D_800E045D[1];
    *dst++ = 7;
    *dst++ = 7;
    return dst;
}
