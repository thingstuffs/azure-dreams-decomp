#include "common.h"

#include "common.h"

extern u16 D_80080AD4;
extern u8 D_8008395C[9];

s32 func_8003F5AC(void) {
    s32 value = D_8008395C[0];

    if (D_80080AD4 != 0) {
        value |= 4;
    } else {
        value &= 0xFF;
    }
    return value;
}
