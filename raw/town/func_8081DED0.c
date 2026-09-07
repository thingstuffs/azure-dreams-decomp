#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef s32 M2C_UNK;

extern void func_800478B8(void *);
extern void func_80053DA8(s32);
extern s32 rand(void);
extern void func_8008F134(void *);
extern s32 func_8008FD9C(void *, void *, void *, void *);

extern s32 D_80012D5C[];
extern Vec3 D_80020020;
extern void *D_80020030[];
extern u8 D_80024420[];
extern s32 D_8002445C[];
extern s32 D_80024628[];
extern s32 D_8007947C[];
extern int D_800814A0;
extern u8 D_80083780[];
extern M2C_UNK D_800D0420;

void func_800206D0(void *arg0, void *arg1, void *arg2)
{
    static void *const sw_keep[] = {
        &&state0, &&state1, &&state2, &&state3,
        &&state4, &&state5, &&state6
    };
    void *object = FIELD(arg0, void *, 4);
    Vec3 local = D_80020020;
    s32 value;
    s32 amount;
    s32 divisor = 1;
    u32 swi;

    if (FIELD(object, u16, 0x20) & 8) {
        FIELD(arg0, s16, 0) = 6;
    }

    swi = (u32)FIELD(arg0, s16, 0);
    if (swi >= 7) {
        goto end;
    }
    (void)sw_keep;
    goto *D_80020030[swi];

state0:
    {
    s32 mode;
    s32 quotient;

    ASM_CLOBBER("$5");
    mode = FIELD(arg0, s16, 0x54);
    switch (mode) {
    case 1:
        divisor = 10;
        goto state0_compute;
    case 2:
        divisor = 100;
        break;
    default:
        goto state0_compute;
    }
state0_compute:
    quotient = FIELD(object, s16, 0x1E) / divisor;
    divisor = quotient % 10;
    if (FIELD(arg0, s16, 0x56) < divisor) {
        FIELD(arg2, u16, 0x14) &= 0xFF7F;
    } else {
        FIELD(arg2, u16, 0x14) |= 0x80;
    }
    FIELD(arg0, u8, 0x1D) = 0;
    goto end;
    }

state1:
    {
    s32 mode;

    FIELD(arg2, s32 *, 0) = D_8007947C;
    FIELD(arg2, s32, 8) = D_8007947C[1];
    FIELD(arg2, u8, 4) = 0;
    FIELD(arg2, u8, 5) = rand() & 3;
    FIELD(arg2, u16, 0x14) &= 0xFF7F;
    mode = FIELD(arg0, s16, 0x54);
    if (mode == 0) {
        FIELD(arg2, u16, 0x12) += 5;
    } else if (mode == 1) {
        FIELD(arg2, u16, 0x12) -= 5;
    }
    FIELD(arg0, u8, 0x1D) = 0;
    FIELD(arg0, s16, 0) = 2;
    }

state2:
    func_800478B8(arg2);
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0x14) += 0x30000;
    value = --FIELD(arg0, u16, 2);
    if ((s16)value > 0) {
        goto end;
    }
    func_80053DA8(0x501);
    FIELD(arg1, s32, 8) = 0xFFC00000;
    FIELD(arg1, s32, 0x14) = ((rand() & 0xFF) << 11) + 0xFFE80000;
    FIELD(arg0, s16, 2) = (rand() & 0xF) + 30;
    FIELD(arg0, s16, 0) = 3;
    goto end;

state3:
    {
        s32 floor = 0xFFC00000;
        s32 object_value;

        func_800478B8(arg2);
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x30000;
        if (floor < FIELD(arg1, s32, 8)) {
            func_80053DA8(0x501);
            FIELD(arg1, s32, 8) = floor;
            FIELD(arg1, s32, 0x14) = -FIELD(arg1, s32, 0x14) >> 1;
        }
        if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
            func_80053DA8(0x516);
            amount = ((s32 *)&local)[FIELD(arg0, s16, 0x54)] * 100;
            D_80012D5C[0] += amount;
            D_80024628[0] += amount;
            FIELD(arg0, s16, 0) = 6;
        }
        value = --FIELD(arg0, u16, 2);
        if ((s16)value > 0) {
            goto end;
        }
        FIELD(arg0, s16, 2) = 180;
        FIELD(arg0, s16, 0) = 4;
        object_value = D_8002445C[FIELD(arg0, s16, 0x54)];
        FIELD(arg2, s16, 0x12) = 0;
        FIELD(arg2, u8, 4) = 0;
        FIELD(arg2, u8, 5) = 0;
        FIELD(arg2, s32, 8) = object_value;
        FIELD(arg1, s32, 8) = floor;
        goto end;
    }

state4:
    if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        amount = ((s32 *)&local)[FIELD(arg0, s16, 0x54)] * 100;
        D_80012D5C[0] += amount;
        D_80024628[0] += amount;
        FIELD(arg0, s16, 0) = 6;
    }
    value = --FIELD(arg0, u16, 2);
    if ((s16)value > 0) {
        goto end;
    }
    FIELD(arg0, s16, 2) = 31;
    FIELD(arg0, s16, 0) = 5;
    goto end;

state5:
    if ((FIELD(arg0, u16, 2) >> 2) & 1) {
        FIELD(arg2, u16, 0x14) |= 0x80;
    } else {
        FIELD(arg2, u16, 0x14) &= 0xFF7F;
    }
    if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        amount = ((s32 *)&local)[FIELD(arg0, s16, 0x54)] * 100;
        D_80012D5C[0] += amount;
        D_80024628[0] += amount;
        FIELD(arg0, s16, 0) = 6;
    }
    value = --FIELD(arg0, u16, 2);
    if ((s16)value > 0) {
        goto end;
    }
    FIELD(arg0, s16, 0) = 6;
    goto end;

state6:
    func_8008F134((u8 *)arg0 + 8);
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
