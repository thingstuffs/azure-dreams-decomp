#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern s8 D_80016000[];

typedef void (*Callback)(s32);

s32 func_8051EAF8(void) {
    void *object;
    void *position;
    Callback callback;
    s32 x;
    s32 y;

    object = *(void **)D_80016000;
    object = FIELD(object, void *, 0x20);
    callback = FIELD(object, Callback, 0x248);
    callback(1);

    object = *(void **)D_80016000;
    position = FIELD(object, void *, 0x1C);
    x = FIELD(position, s32, 4);
    y = FIELD(position, s32, 8);
    if ((u32)(x - 0x341) < 0x5FU) {
        if (y < 0x3F0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: The global is an established byte array, so both pointer loads use
   the D_80016000 hi/lo address form. Separate reloads straddle the indirect call;
   sibling scalar locals eagerly load both fields; nested explicit returns encode
   the retail two-branch result CFG without boolean-materialization moves. */
