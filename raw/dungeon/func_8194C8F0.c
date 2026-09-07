#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8004491C(void *, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800644B8(s32);
extern void func_80024228() __attribute__((noreturn));
extern void func_800243F8() __attribute__((noreturn));
extern void func_80024468() __attribute__((noreturn));
extern void func_80024478() __attribute__((noreturn));

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 *D_800E3D18;

void func_800240F0(void *arg0, void *arg1, void *arg2)
{
    register u16 stv ASM_REG("$2");
    u16 vec[3];
    s32 state;

    state = FIELD(arg0, s16, 0xC);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        func_80024468();
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    func_80024468();

state_zero:
    func_8004491C((u8 *)arg0 - 0x20, &D_80045340);
    FIELD(arg0, u16, 0xC) = FIELD(arg0, u16, 0xC) + 1;
state_one:
    {
        void *source;
        source = FIELD(FIELD(arg0, void *, 0), void *, 0xC);
        if ((FIELD(source, u16, 0x14) & 0x8000) ||
            func_8003DE58(FIELD(source, void *, 8), source, vec, 0) != 0) {
            void *position;
            u16 z;

            position = FIELD(FIELD(arg0, void *, 0), void *, 8);
            FIELD(arg1, u16, 2) = FIELD(position, u16, 2);
            FIELD(arg1, u16, 6) = FIELD(position, u16, 6);
            z = FIELD(position, u16, 0xA);
            FIELD(arg1, u16, 0xA) = z;

            if (!(FIELD(source, u16, 0x14) & 0x8000)) {
                u16 w;

                FIELD(arg1, u16, 2) += vec[0];
                FIELD(arg1, u16, 6) += vec[1];
                w = FIELD(arg1, u16, 0xA) + vec[2];
                ASM_TAILSLOT_PIN(w);
                func_80024228();
            }
            ASM_SCHED_BARRIER();
            FIELD(arg1, u16, 0xA) = z - 0x20;
        }
    }

    if (FIELD(FIELD(arg0, void *, 8), u16, 0) & 0x80) {
        register u16 ten ASM_REG("$3");

        ten = 10;
        ASM_KEEP_NV(ten);
        stv = FIELD(arg0, volatile u16, 0xC);
        FIELD(arg0, u16, 0x10) = ten;
        func_800243F8();
    }
    goto tick;

state_two:
    {
        u16 h;
        h = FIELD(arg2, u16, 0x1E) + 0x200;
        FIELD(arg2, u16, 0x1E) = h;
        FIELD(arg2, u16, 0x1C) = h;
    }
    {
        void *position;
        position = FIELD(FIELD(arg0, void *, 4), void *, 8);
        FIELD(arg1, s32, 0xC) = FIELD(position, s32, 0);
        FIELD(arg1, s32, 0x10) = FIELD(position, s32, 4);
    }
    FIELD(arg1, s32, 0x14) = (FIELD(D_800814A8, s16, 0x88) - 0x50) << 16;

    {
        s32 k;
        k = (D_80083228 + FIELD(D_800814A8, s16, 0x2A) + 0x100) >> 7;
        if (func_8003DE58(*(void **)((k & 0x1C) + (s32)D_800E3D18),
                          D_80082E80, vec, 0) != 0) {
            FIELD(arg1, s32, 0xC) += ((s16 *)vec)[0] << 16;
            FIELD(arg1, s32, 0x10) += ((s16 *)vec)[1] << 16;
            FIELD(arg1, s32, 0x14) += ((s16 *)vec)[2] << 16;
        }
    }

    FIELD(arg1, s32, 0) +=
        (FIELD(arg1, s32, 0xC) - FIELD(arg1, s32, 0)) /
        FIELD(arg0, s16, 0x10);
    FIELD(arg1, s32, 4) +=
        (FIELD(arg1, s32, 0x10) - FIELD(arg1, s32, 4)) /
        FIELD(arg0, s16, 0x10);
    FIELD(arg1, s32, 8) +=
        (FIELD(arg1, s32, 0x14) - FIELD(arg1, s32, 8)) /
            FIELD(arg0, s16, 0x10) -
        (func_800644B8(FIELD(arg0, s16, 0x10) * 0xAA) << 7);

    {
        u16 c;
        c = FIELD(arg0, u16, 0x10) - 1;
        FIELD(arg0, u16, 0x10) = c;
        if ((s16)c > 0) {
            goto tick;
        }
    }

    FIELD(arg1, s32, 0) = FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 0x14);
    stv = FIELD(arg0, u16, 0xC);
    FIELD(arg0, u16, 0x10) = state;

adv:
    FIELD(arg0, u16, 0xC) = stv + 1;
    func_80024468();

state_three:
    {
        u16 h;
        u8 b;
        h = FIELD(arg2, u16, 0x1E) + 0x200;
        b = FIELD(arg2, u8, 0xE) + 8;
        FIELD(arg2, u16, 0x1E) = h;
        FIELD(arg2, u16, 0x1C) = h;
        FIELD(arg2, u8, 0xE) = b;
        FIELD(arg2, u8, 0xD) = b;
        FIELD(arg2, u8, 0xC) = b;
    }
    {
        u16 c;
        c = FIELD(arg0, u16, 0x10) - 1;
        FIELD(arg0, u16, 0x10) = c;
        if ((s16)c > 0) {
            goto tick;
        }
    }

    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    func_80024478();

tick:
    FIELD(arg0, u16, 0x12) = FIELD(arg0, u16, 0x12) + 1;
}
