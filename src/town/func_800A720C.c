#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(s32 *);

extern void func_800A4A58(void);
extern s16 D_8006ADD4;
extern s8 D_800D1554;
extern s32 D_80100D90;
extern s32 D_80100DB8[];
extern s32 D_80100DE0[];

void func_800A496C(void)
{
    s32 *base0;
    s32 *base1;
    Callback callback;

    base0 = D_80100DE0;
    base1 = D_80100DB8;

    callback = FIELD(base0, Callback, 0x24);
    if (callback != NULL) {
        callback(base0);
    }
    if (FIELD(base1, Callback, 0x1C) != NULL) {
        FIELD(base1, Callback, 0x1C)(base1);
    }
    if (FIELD(base0, Callback, 0x28) != NULL) {
        FIELD(base0, Callback, 0x28)(base0);
    }
    if (FIELD(base1, Callback, 0x20) != NULL) {
        FIELD(base1, Callback, 0x20)(base1);
    }

    func_800A4A58();
    if (D_8006ADD4 != 0xC) {
        if (*(s16 *)(D_80100D90 + 6) < 0x600) {
            D_800D1554 = 1;
            return;
        }
        D_800D1554 = 0;
    }
}

/* MECHANISM: Held D_80100DE0/D_80100DB8 as distinct bases to produce the exact s0/s1 prologue.
   Named only the first callback live range; inline later loads naturally color v1 then v0.
   Restored the flag=1 tail-call delay-slot store, completing the exact 56-word CFG. */
