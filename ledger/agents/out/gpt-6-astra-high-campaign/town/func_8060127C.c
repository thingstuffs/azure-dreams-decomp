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

/* Call the callback with fixed arguments and cache three quarters of its result. */
u32 func_8060127C(void) {
    s8 callback_args[4];
    u32 scaled_result;

    callback_args[1] = 1;
    callback_args[0] = 1;
    callback_args[2] = 0;
    callback_args[3] = 0;
    scaled_result = (u32) (D_80016000->inner->callback(callback_args) * 3) >> 2;
    D_80017FB8 = scaled_result;
    return scaled_result;
}
