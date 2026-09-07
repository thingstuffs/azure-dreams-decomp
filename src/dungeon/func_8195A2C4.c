#include "common.h"

typedef struct Inner {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
    s32 fieldC;
} Inner;

typedef struct Outer {
    u8 pad0[8];
    Inner *inner8;
    Inner *innerC;
    u8 pad10[0xE];
    u16 flags1E;
} Outer;

extern u16 D_800281F8[];
extern s32 D_800814A0[];
extern void func_80025B54(void) __attribute__((noreturn));

void func_8195A2C4(void *arg0, Inner *arg1, Inner *arg2)
{
    Outer *outer;
    Inner *inner;
    s32 flagged;

    outer = *(Outer **)((u8 *)arg0 + 8);
    flagged = outer->flags1E & 0x8000;
    D_800281F8[0]++;
    if (flagged != 0) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80025B54();
    }
    arg2->fieldC = outer->innerC->fieldC;
    inner = (*(Outer **)((u8 *)arg0 + 8))->inner8;
    arg1->field2 = inner->field2;
    arg1->field6 = inner->field6;
    arg1->fieldA = inner->fieldA;
}
