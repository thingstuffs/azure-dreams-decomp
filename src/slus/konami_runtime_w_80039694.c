#include "common.h"

#include "common.h"

typedef struct Func80039694State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
} Func80039694State;

extern s32 func_80033B2C(s32 arg0);

u32 func_80039694(Func80039694State *arg0) {
    u32 ptr = (u32)arg0->read_ptr;
    u32 lo = *(u8 *)ptr;
    u32 hi = *(u8 *)(ptr + 1);
    s16 key = (s16)(lo + (hi << 8));
    u32 value;

    arg0->read_ptr = (u8 *)(ptr + 2);
    if (func_80033B2C(key) == 0) {
        u32 next = (u32)arg0->read_ptr + 4;
        arg0->read_ptr = (u8 *)next;
        return next;
    } else {
        u8 *data = arg0->read_ptr;
        value = data[0] + (data[1] << 8) + (data[2] << 16) + (data[3] << 24);
        arg0->read_ptr = (u8 *)value;
        return value;
    }
}
