#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef s32 M2C_UNK;

extern void func_800239BC(void) __attribute__((noreturn));
extern void func_80023A74(void) __attribute__((noreturn));
extern void func_80023B5C(void) __attribute__((noreturn));
extern void func_80023BAC(void) __attribute__((noreturn));
extern void func_800478B8(void *);
extern void func_80053DA8(s32);
extern s32 rand(void);
extern void func_8008F134(void *);
extern s32 func_8008FD9C(void *, void *, void *, void *);

extern s32 D_80012D5C[];
extern Vec3 D_80020278;
extern u8 D_80024488[];
extern s32 D_800244DC[];
extern s32 D_80024628[];
extern s32 D_800814A0;
extern u8 D_80083780[];
extern M2C_UNK D_800D0420;

void func_800236BC(void *arg0, void *arg1, void *arg2)
{
    Vec3 local = D_80020278;
    s16 state;
    s32 value;
    s32 amount;
    s32 *localp = (s32 *)&local;
    register u32 speculative_page ASM_REG("$4");

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    FIELD(FIELD(arg0, void *, 0), u16, 0x62) |= 2;

    state = FIELD(arg0, s16, 4);
    if (state == 2) {
        goto state_2;
    }
    if (state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        return func_80023BAC();
    }
    if (state == 4) {
        goto state_4;
    }
    if (state < 4) {
        goto state_3;
    }
    if (state == 255) {
        goto state_255;
    }
    return func_80023BAC();

state_0:
        func_800478B8(arg2);
        FIELD(arg1, s32, 0x14) += 0x40000;
        FIELD(arg0, u8, 0x1D) = 0;
        if (FIELD(arg1, s32, 8) < 0) {
            return;
        }
        func_80053DA8(0x501);
        FIELD(arg1, s32, 8) = 0;
        FIELD(arg0, s16, 6) = 15;
        FIELD(arg1, s32, 0xC) = ((rand() % 320) - 64) << 12;
        FIELD(arg1, s32, 0x10) = (rand() % 96 + 128) << 12;
        FIELD(arg1, s32, 0x14) = 0xFFF00000;
        FIELD(arg0, u16, 4)++;
        return func_80023BAC();

state_1:
        func_800478B8(arg2);
        FIELD(arg1, s32, 0x14) += 0x40000;
        FIELD(arg0, u16, 6)--;
        if (FIELD(arg1, s32, 8) < 0) {
            return;
        }
        func_80053DA8(0x501);
        if (FIELD(arg0, s16, 6) > 0) {
            FIELD(arg1, s32, 8) = 0;
            FIELD(arg1, s32, 0x14) = -FIELD(arg1, s32, 0x14);
            return func_80023BAC();
        }
        FIELD(arg1, s32, 8) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg1, s32, 0x14) = ((rand() & 0xFF) << 11) - 0x150000;
        FIELD(arg0, s16, 6) = (rand() & 0xF) + 30;
        FIELD(arg0, u16, 4)++;
        return func_80023BAC();

state_2:
        func_800478B8(arg2);
        FIELD(arg1, s32, 0x14) += 0x30000;
        FIELD(arg0, u16, 6)--;
        speculative_page = 0x80020000;
        if (FIELD(arg1, s32, 8) < 0) {
            goto state_2_collision;
        }
        FIELD(arg1, s32, 8) = 0;
        if (FIELD(arg0, s16, 6) < 0) {
            value = D_800244DC[FIELD(arg0, s16, 0x54)];
            FIELD(arg2, s16, 0x12) = 0;
            FIELD(arg2, u8, 4) = 0;
            FIELD(arg2, u8, 5) = 0;
            FIELD(arg2, s32, 8) = value;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg0, s16, 6) = 150;
            FIELD(arg0, u16, 4)++;
            return func_800239BC();
        }
        FIELD(arg1, s32, 0x14) = -FIELD(arg1, s32, 0x14) >> 1;
        ASM_KEEP(speculative_page);
        speculative_page = 0x80020000;
state_2_collision:
        speculative_page += 0x4488;
        if (func_8008FD9C((void *)speculative_page, arg1, &D_800D0420, D_80083780) == 0) {
            return;
        }
        func_80053DA8(0x516);
        {
            register s32 tail_value ASM_REG("$3");
            register u32 page ASM_REG("$4");
            u8 *frame;
            frame = __builtin_alloca(0);
            tail_value = *(s32 *)(FIELD(arg0, s16, 0x54) * 4 + frame);
            ASM_KEEP(tail_value);
            page = 0x80010000;
            ASM_PAGEBASE_PIN(page);
            return func_80023A74();
        }

state_3:
        FIELD(arg0, u16, 6)--;
        if (FIELD(arg0, s16, 6) < 0) {
            FIELD(arg0, s16, 6) = 31;
            FIELD(arg0, u16, 4)++;
        }
        if (func_8008FD9C(D_80024488, arg1, &D_800D0420, D_80083780) == 0) {
            return;
        }
        func_80053DA8(0x516);
        amount = localp[FIELD(arg0, s16, 0x54)] * 100;
        D_80012D5C[0] += amount;
        D_80024628[0] += amount;
        FIELD(arg0, s16, 4) = 255;
        return func_80023BAC();

state_4:
        if (func_8008FD9C(D_80024488, arg1, &D_800D0420, D_80083780) != 0) {
            func_80053DA8(0x516);
            amount = localp[FIELD(arg0, s16, 0x54)] * 100;
            D_80012D5C[0] += amount;
            D_80024628[0] += amount;
            FIELD(arg0, s16, 4) = 255;
        }
        if ((FIELD(arg0, u16, 6) >> 2) & 1) {
            register s32 tail_value ASM_REG("$2");
            tail_value = FIELD(arg2, u16, 0x14) | 0x80;
            ASM_TAILSLOT_PIN(tail_value);
            return func_80023B5C();
        }
        FIELD(arg2, u16, 0x14) &= 0xFF7F;
        FIELD(arg0, u16, 6)--;
        if (FIELD(arg0, s16, 6) > 0) {
            return;
        }
        FIELD(arg0, s16, 4) = 255;
        return func_80023BAC();

state_255:
        func_8008F134((u8 *)arg0 + 8);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
}
