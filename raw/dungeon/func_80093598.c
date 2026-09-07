#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80048A44();
extern void func_800982A8();
extern void func_80098614();
extern void func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern void func_800A56E0();
extern void func_800A5720();
extern void *func_800A8608();

extern u8 D_80081484[];
extern s16 D_80083228;
extern u8 D_8008D470[];
extern u8 D_800DD0B8[8];
extern u8 D_800E08CC[];
extern u8 D_800E08E5[];
extern u8 D_800E08F1[];
extern u8 D_800E0919[];

void *func_80098CF8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *s3 ASM_REG("$19") = arg0;
    register s32 s6 ASM_REG("$22") = arg1;
    register void *s5 ASM_REG("$21") = arg2;
    register void *s2 ASM_REG("$18") = arg3;
    register void *s4 ASM_REG("$20") = arg0;
    register void *s0;
    register s32 s1 ASM_REG("$17");
    void *object;
    void *primitive;
    void *state;
    register void *message ASM_REG("$4");
    s32 value;

    s0 = D_80081484;
    if ((s2 != s0) && (FIELD(s0, u8, 1) != 0)) {
        s1 = func_800990FC();
        value = func_8009929C(8, s1);
        value = func_80099368(s2, value);
        value = func_80099194(D_800E08CC, value);
        value = func_80099368(s0, value);
        message = D_800E08E5;
print_message:
        value = func_80099194(message, value);
        func_80099290(value);
        func_800A5720(s1);
        ASM_KEEP(s3);
        ASM_KEEP(s6);
        ASM_KEEP(s5);
        ASM_KEEP(s2);
        ASM_KEEP(s4);
        ASM_KEEP(s0);
        ASM_KEEP(s1);
        goto return_zero;
    }

    if (FIELD(s2, u8, 3) & 0x20) {
        s1 = func_800990FC();
        s0 = (void *)func_8009929C(8, s1);
        if (FIELD(s2, u8, 3) & 0x40) {
            func_800A56E0(0x70A);
            value = func_80099368(s2, s0);
            message = D_800E08F1;
            goto print_message;
        }

        value = func_80099368(s2, s0);
        value = func_80099194(D_800E0919, value);
        func_80099290(value);
        func_800A5720(s1);
        if (FIELD(s2, u8, 1) == 0x11) {
            func_80098614(s4, s2);
            goto allocate;
        }
        func_800982A8(s4, s2);
        goto allocate;
    }
    goto allocate;

allocate:
    object = func_800A8608((u8 *)s3 - 0x20, s2, 0, 0, 0);
    s0 = object;
    if (s0 == 0) {
        goto return_zero;
    }

    {
    s32 coord;

    FIELD(s0, void *, 0x10) = D_8008D470;
    primitive = FIELD(s0, void *, 8);
    FIELD(primitive, s16, 2) = (FIELD(s5, u8, 0x24) << 6) + 0x20;
    FIELD(primitive, s16, 6) = (FIELD(s5, u8, 0x25) << 6) + 0x20;
    coord = FIELD(s4, u16, 0x88);
    ASM_KEEP(coord);
    message = s5;
    FIELD(primitive, s16, 0xA) = coord - 0x30;
    ASM_KEEP(primitive);

    state = (u8 *)s0 + 0x20;
    ASM_KEEP(state);
    {
    register s32 a1 ASM_REG("$5");
    register s32 a2 ASM_REG("$6");

    a1 = FIELD(s2, s32, 0);
    FIELD(state, s16, 0xAC) = 1;
    FIELD(state, void *, 0x90) = message;
    FIELD(state, s32, 0x8C) = s6;
    FIELD(state, s16, 0xA8) = 6;
    FIELD(state, s32, 0x98) = a1;
    a1 = 0x80080000;
    ASM_KEEP(a1);
    FIELD(s3, void *, 0xBC) = s2;
    a2 = FIELD(s2, s32, 0);
    FIELD(state, void *, 0x9C) = (u8 *)a1 + 0x1484;
    FIELD(s3, s32, 0x8C) = 0;
    FIELD(s3, s32, 0x124) = 0;
    FIELD((void *)a1, s32, 0x1484) = a2;
    a1 = (s32)D_800DD0B8;
    FIELD(s3, s8, 0x9A) = 0x1B;
    FIELD(s3, s8, 0x9B) = 0;
    FIELD(message, void *, 0x2C) = (void *)a1;

    func_80048A44(
        message,
        ((u8 *)a1)[((D_80083228 + FIELD(s4, s16, 0x2A) + 0x100) >> 9) & 7],
        0,
        1);
    func_800A56E0(0x511);
    FIELD(s4, s32, 0x1C) |= 0x100000;
    func_80098B38(s2);
    }
    }
    return s0;

return_zero:
    return 0;
}

/* MECHANISM: The true-space CFG places the shared message tail above its backward caller.
   Scoped guarded pins reproduce the s3/s6/s5/s2/s4 and a0/a1/a2 live ranges.
   A held 0x80080000 page base plus named fences preserves the retail tail order. */
