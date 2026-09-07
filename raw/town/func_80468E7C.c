#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(s32);

extern s8 D_80016000[];

void func_80019E7C(void *arg0)
{
    void *root;
    u8 *base;
    s32 *object;
    u16 amount;

    root = *(void **)D_80016000;
    FIELD(FIELD(root, void *, 0x20), Callback, 0x258)(1);

    base = *(u8 **)D_80016000;
    object = FIELD(base, s32 *, 0x1C);
    object[1] += *(s16 *)arg0;
    amount = *(u16 *)((u8 *)arg0 + 2);
    base = FIELD(base, u8 *, 0x1C);
    FIELD(base, s32, 8) += (s16)amount / 2 - 0x40;
    
}

/* MECHANISM: The established byte-array global retains the 0x8001 page across
   the call; the runtime base is held in a1 and overwritten by its object load.
   A compound field update interleaves its load with the signed /2 lowering. */
