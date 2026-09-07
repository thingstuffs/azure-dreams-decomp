#include "common.h"

extern s16 func_8008CF48();

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk800C5388;

s16 func_800C2AE8(void *arg0) {
    Unk800C5388 sp10;
    long long sp28;
    long long *sp30;

    sp10.unk0 = *(s32 *)((s8 *)arg0 + 0);
    sp10.unk4 = *(s32 *)((s8 *)arg0 + 4);
    sp30 = &sp28;
    sp10.unk8 = *(s32 *)((s8 *)arg0 + 8) + 0xFFF80000;
    return func_8008CF48(&sp10, &sp30);
}

/* MECHANISM: A 24-byte escaped record plus an 8-byte pointee force the retail 0x40 frame.
   Copying both leading fields before linking sp30 to sp28 delays that address live range,
   reproducing the exact prologue, stack-store order, callee ABI setup, and s16 return. */
