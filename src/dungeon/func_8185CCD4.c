#include "common.h"

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);
extern s16 D_80083160[];
extern u8 D_800DEAE0[];

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_8185CCD4(void *arg0, void *arg1, void *arg2)
{
    s16 angle;
    s16 *angles;
    void *inner;

    inner = *(void **)arg0;
    U16_AT(inner, 0x14) = U16_AT(inner, 0x14) + 1;
    S32_AT(arg2, 0xC) = S32_AT(arg2, 0xC) + 0xFFF7F7F8;

    angle = U16_AT(arg0, 0x1C) + U16_AT(arg0, 0x1E);
    angles = D_80083160;
    U16_AT(arg0, 0x1C) = angle;
    U16_AT(arg0, 0x1C) = angle % 0x1000;
    U16_AT(arg0, 0x20) = U16_AT(arg0, 0x20) + 4;

    S16_AT(arg1, 2) = U16_AT(arg0, 6) +
        (((func_800644B8(S16_AT(arg0, 0x1C)) >> 4) *
          S16_AT(arg0, 0x20)) >> 8);
    S16_AT(arg1, 6) = U16_AT(arg0, 0xA) +
        (((func_80064584(S16_AT(arg0, 0x1C)) >> 4) *
          S16_AT(arg0, 0x20)) >> 8);
    S16_AT(arg2, 0x1A) =
        (s32)(0 - ((func_80064584(S16_AT(arg0, 0x1C) - angles[100]) >> 4) << 8)) >> 8;

    func_800478B8(arg2);
    if (U16_AT(arg2, 0x14) & 0x6000) {
        func_8003DB94(arg2, D_800DEAE0, 0);
    }
}
