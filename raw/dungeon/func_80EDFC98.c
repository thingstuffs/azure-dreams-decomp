#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

void *func_8003FD64();
s32 func_8003DE58();
s32 func_8004491C();
s32 rand();
s32 func_801710B8();

extern u8 D_80170ED8[];
extern u8 D_801712C4[];

void func_80171498(
    void *arg0, s16 arg1, s32 arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;
    register s32 held_arg5 ASM_REG("$19") = arg5;
    register s32 held_arg6 ASM_REG("$20") = arg6;
    volatile u16 sp10;
    volatile u16 sp12;
    volatile u16 sp14;
    s16 counter;
    s32 color0;
    s32 color1;
    void *source;
    void *effect;
    void *base;

    effect = func_8003FD64(0x211, arg0);
    if (effect != NULL) {
        FIELD(effect, void *, 0x10) = D_801712C4;

        FIELD(FIELD(effect, void *, 8), s16, 2) =
            FIELD(FIELD(arg0, void *, 8), u16, 2) + held_arg4;
        FIELD(FIELD(effect, void *, 8), s16, 6) =
            FIELD(FIELD(arg0, void *, 8), u16, 6) + held_arg5;
        FIELD(FIELD(effect, void *, 8), s16, 0xA) =
            FIELD(FIELD(arg0, void *, 8), u16, 0xA) + held_arg6;
        ASM_KEEP(held_arg4);
        ASM_KEEP(held_arg5);
        ASM_KEEP(held_arg6);

        source = FIELD(arg0, void *, 0xC);
        if (func_8003DE58(FIELD(source, s32, 8), source, &sp10, 0) != 0) {
            FIELD(FIELD(effect, void *, 8), s16, 2) += sp10;
            FIELD(FIELD(effect, void *, 8), s16, 6) += sp12;
            FIELD(FIELD(effect, void *, 8), s16, 0xA) += sp14;
        }

        base = (u8 *)effect + 0x20;
        FIELD(base, s16, 0x5A) = FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(base, s16, 0x5E) = FIELD(FIELD(arg0, void *, 8), u16, 6);
        FIELD(base, s16, 0x62) = FIELD(FIELD(arg0, void *, 8), u16, 0xA);

        source = FIELD(arg0, void *, 0xC);
        if (func_8003DE58(FIELD(source, s32, 8), source, &sp10, 0) != 0) {
            FIELD(base, s16, 0x5A) += sp10;
            FIELD(base, s16, 0x5E) += sp12;
            FIELD(base, s16, 0x62) += sp14;
        }

        FIELD(base, s16, 0x36) = FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(base, s16, 0x38) = FIELD(FIELD(arg0, void *, 8), u16, 6);
        FIELD(base, s16, 0x3A) = FIELD(FIELD(arg0, void *, 8), u16, 0xA);

        counter = 0;
        do {
            func_801710B8(base, FIELD(effect, void *, 8), FIELD(effect, void *, 0xC));
            counter++;
        } while (counter < 10);

        FIELD(base, s16, 0x14) = arg1;
        FIELD(base, s16, 0x32) = arg3;
        func_8004491C(effect, D_80170ED8);

        color0 = rand();
        color1 = rand();
        FIELD(base, s32, 0) =
            ((color0 & 0xFF) << 16) |
            ((color1 & 0xFF) << 8) |
            (rand() & 0xFF);
        FIELD(base, s32, 8) = FIELD(base, s32, 0);
    }
}
