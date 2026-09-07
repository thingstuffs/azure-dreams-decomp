#include "common.h"

typedef s32 (*Callback)(s8 *);

typedef struct Inner {
    u8 pad[0x50];
    Callback callback;
} Inner;

typedef struct Outer {
    u8 pad[0x20];
    Inner *inner;
} Outer;

extern Outer *D_80016000;
extern u32 D_80017FB8;

u32 func_8060127C(void) {
    s8 args[4];
    u32 result;

    args[1] = 1;
    args[0] = 1;
    args[2] = 0;
    args[3] = 0;
    result = (u32) (D_80016000->inner->callback(args) * 3) >> 2;
    D_80017FB8 = result;
    return result;
}
