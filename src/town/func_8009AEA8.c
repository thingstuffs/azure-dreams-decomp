#include "common.h"

extern void func_80099754(void *);
extern u8 D_80098544[8];

void func_80098608(void *arg0, void *arg1) {
    u16 timer;
    s32 value;

    timer = *(u16 *)((u8 *)arg0 + 0xA) - 1;
    *(u16 *)((u8 *)arg0 + 0xA) = timer;
    if ((timer << 16) > 0) {
        value = *(s32 *)((u8 *)arg1 + 8);
        value += ((s32)0xFF800000 - value) / 2;
        *(s32 *)((u8 *)arg1 + 8) = value;
        return;
    }

    *(s32 *)((u8 *)arg1 + 8) = (s32)0xFF800000;
    func_80099754(arg1);
    *(u16 *)((u8 *)arg0 + 0xA) = 10;
    *(void **)((u8 *)arg0 + 4) = D_80098544;
}

/* MECHANISM: The arg0 record remains live in s0 across the returning call.
   The positive path uses signed divide-by-two rounding and an arg-sibcall tail;
   an 8-byte extern forces the final address to use a hi/lo pair. */
