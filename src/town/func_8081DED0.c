#include "common.h"


typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef s32 M2C_UNK;

typedef struct S_800206D0_0 {
    s16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    void * unk_04;
    u8 pad_08[0x15];
    u8 unk_1D;
    u8 pad_1E[0x36];
    s16 unk_54;
    s16 unk_56;
} S_800206D0_0;   /* arg0 in func_800206D0 */

typedef struct S_800206D0_1 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u16 unk_20;
} S_800206D0_1;   /* object in func_800206D0 */

typedef struct S_800206D0_2 {
    s32 * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x6];
    union { u16 s; s16 u; } unk_12;   /* accessed as both */
    u16 unk_14;
} S_800206D0_2;   /* arg2 in func_800206D0 */

typedef struct S_800206D0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800206D0_3;   /* arg1 in func_800206D0 */


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
    void *object = ((S_800206D0_0 *)arg0)->unk_04;
    Vec3 local = D_80020020;
    s32 value;
    s32 amount;
    s32 divisor = 1;
    u32 swi;

    if (((S_800206D0_1 *)object)->unk_20 & 8) {
        ((S_800206D0_0 *)arg0)->unk_00 = 6;
    }

    swi = (u32)((S_800206D0_0 *)arg0)->unk_00;
    if (swi >= 7) {
        goto end;
    }
    (void)sw_keep;
    goto *D_80020030[swi];

state0:
    {
    s32 mode;
    s32 quotient;

    ASM_CLOBBER("$5");   /* MATCH pin: retail register colouring depends on it */
    mode = ((S_800206D0_0 *)arg0)->unk_54;
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
    quotient = ((S_800206D0_1 *)object)->unk_1E / divisor;
    divisor = quotient % 10;
    if (((S_800206D0_0 *)arg0)->unk_56 < divisor) {
        ((S_800206D0_2 *)arg2)->unk_14 &= 0xFF7F;
    } else {
        ((S_800206D0_2 *)arg2)->unk_14 |= 0x80;
    }
    ((S_800206D0_0 *)arg0)->unk_1D = 0;
    goto end;
    }

state1:
    {
    s32 mode;

    ((S_800206D0_2 *)arg2)->unk_00 = D_8007947C;
    ((S_800206D0_2 *)arg2)->unk_08 = D_8007947C[1];
    ((S_800206D0_2 *)arg2)->unk_04 = 0;
    ((S_800206D0_2 *)arg2)->unk_05 = rand() & 3;
    ((S_800206D0_2 *)arg2)->unk_14 &= 0xFF7F;
    mode = ((S_800206D0_0 *)arg0)->unk_54;
    if (mode == 0) {
        ((S_800206D0_2 *)arg2)->unk_12.s += 5;
    } else if (mode == 1) {
        ((S_800206D0_2 *)arg2)->unk_12.s -= 5;
    }
    ((S_800206D0_0 *)arg0)->unk_1D = 0;
    ((S_800206D0_0 *)arg0)->unk_00 = 2;
    }

state2:
    func_800478B8(arg2);
    ((S_800206D0_3 *)arg1)->unk_00 += ((S_800206D0_3 *)arg1)->unk_0C;
    ((S_800206D0_3 *)arg1)->unk_04 += ((S_800206D0_3 *)arg1)->unk_10;
    ((S_800206D0_3 *)arg1)->unk_08 += ((S_800206D0_3 *)arg1)->unk_14;
    ((S_800206D0_3 *)arg1)->unk_14 += 0x30000;
    value = --((S_800206D0_0 *)arg0)->unk_02.s;
    if ((s16)value > 0) {
        goto end;
    }
    func_80053DA8(0x501);
    ((S_800206D0_3 *)arg1)->unk_08 = 0xFFC00000;
    ((S_800206D0_3 *)arg1)->unk_14 = ((rand() & 0xFF) << 11) + 0xFFE80000;
    ((S_800206D0_0 *)arg0)->unk_02.u = (rand() & 0xF) + 30;
    ((S_800206D0_0 *)arg0)->unk_00 = 3;
    goto end;

state3:
    {
        s32 floor = 0xFFC00000;
        s32 object_value;

        func_800478B8(arg2);
        ((S_800206D0_3 *)arg1)->unk_08 += ((S_800206D0_3 *)arg1)->unk_14;
        ((S_800206D0_3 *)arg1)->unk_14 += 0x30000;
        if (floor < ((S_800206D0_3 *)arg1)->unk_08) {
            func_80053DA8(0x501);
            ((S_800206D0_3 *)arg1)->unk_08 = floor;
            ((S_800206D0_3 *)arg1)->unk_14 = -((S_800206D0_3 *)arg1)->unk_14 >> 1;
        }
        if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
            func_80053DA8(0x516);
            amount = ((s32 *)&local)[((S_800206D0_0 *)arg0)->unk_54] * 100;
            D_80012D5C[0] += amount;
            D_80024628[0] += amount;
            ((S_800206D0_0 *)arg0)->unk_00 = 6;
        }
        value = --((S_800206D0_0 *)arg0)->unk_02.s;
        if ((s16)value > 0) {
            goto end;
        }
        ((S_800206D0_0 *)arg0)->unk_02.u = 180;
        ((S_800206D0_0 *)arg0)->unk_00 = 4;
        object_value = D_8002445C[((S_800206D0_0 *)arg0)->unk_54];
        ((S_800206D0_2 *)arg2)->unk_12.u = 0;
        ((S_800206D0_2 *)arg2)->unk_04 = 0;
        ((S_800206D0_2 *)arg2)->unk_05 = 0;
        ((S_800206D0_2 *)arg2)->unk_08 = object_value;
        ((S_800206D0_3 *)arg1)->unk_08 = floor;
        goto end;
    }

state4:
    if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        amount = ((s32 *)&local)[((S_800206D0_0 *)arg0)->unk_54] * 100;
        D_80012D5C[0] += amount;
        D_80024628[0] += amount;
        ((S_800206D0_0 *)arg0)->unk_00 = 6;
    }
    value = --((S_800206D0_0 *)arg0)->unk_02.s;
    if ((s16)value > 0) {
        goto end;
    }
    ((S_800206D0_0 *)arg0)->unk_02.u = 31;
    ((S_800206D0_0 *)arg0)->unk_00 = 5;
    goto end;

state5:
    if ((((S_800206D0_0 *)arg0)->unk_02.s >> 2) & 1) {
        ((S_800206D0_2 *)arg2)->unk_14 |= 0x80;
    } else {
        ((S_800206D0_2 *)arg2)->unk_14 &= 0xFF7F;
    }
    if (func_8008FD9C(D_80024420, arg1, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        amount = ((s32 *)&local)[((S_800206D0_0 *)arg0)->unk_54] * 100;
        D_80012D5C[0] += amount;
        D_80024628[0] += amount;
        ((S_800206D0_0 *)arg0)->unk_00 = 6;
    }
    value = --((S_800206D0_0 *)arg0)->unk_02.s;
    if ((s16)value > 0) {
        goto end;
    }
    ((S_800206D0_0 *)arg0)->unk_00 = 6;
    goto end;

state6:
    func_8008F134((u8 *)arg0 + 8);
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
