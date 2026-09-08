#include "common.h"
#include "records/Rec_func_800206D0_arg1.h"


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

/* Updates a bouncing pickup, awards its value on collection, and expires it. */
void func_800206D0(void *pickup, void *motion, void *sprite)
{
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3,
        &&state4, &&state5, &&state6
    };
    void *source_object = ((S_800206D0_0 *)pickup)->unk_04;
    Vec3 reward_units = D_80020020;
    s32 timer;
    s32 reward;
    s32 divisor = 1;
    u32 state;

    if (((S_800206D0_1 *)source_object)->unk_20 & 8) {
        ((S_800206D0_0 *)pickup)->unk_00 = 6;
    }

    state = (u32)((S_800206D0_0 *)pickup)->unk_00;
    if (state >= 7) {
        goto end;
    }
    (void)state_labels;
    goto *D_80020030[state];

state0:
    {
        s32 denomination;
        s32 scaled_count;

        ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        denomination = ((S_800206D0_0 *)pickup)->unk_54;
        switch (denomination) {
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
        scaled_count = ((S_800206D0_1 *)source_object)->unk_1E / divisor;
        divisor = scaled_count % 10;
        if (((S_800206D0_0 *)pickup)->unk_56 < divisor) {
            ((S_800206D0_2 *)sprite)->unk_14 &= 0xFF7F;
        } else {
            ((S_800206D0_2 *)sprite)->unk_14 |= 0x80;
        }
        ((S_800206D0_0 *)pickup)->unk_1D = 0;
        goto end;
    }

state1:
    {
        s32 denomination;

        ((S_800206D0_2 *)sprite)->unk_00 = D_8007947C;
        ((S_800206D0_2 *)sprite)->unk_08 = D_8007947C[1];
        ((S_800206D0_2 *)sprite)->unk_04 = 0;
        ((S_800206D0_2 *)sprite)->unk_05 = rand() & 3;
        ((S_800206D0_2 *)sprite)->unk_14 &= 0xFF7F;
        denomination = ((S_800206D0_0 *)pickup)->unk_54;
        if (denomination == 0) {
            ((S_800206D0_2 *)sprite)->unk_12.s += 5;
        } else if (denomination == 1) {
            ((S_800206D0_2 *)sprite)->unk_12.s -= 5;
        }
        ((S_800206D0_0 *)pickup)->unk_1D = 0;
        ((S_800206D0_0 *)pickup)->unk_00 = 2;
    }

state2:
    func_800478B8(sprite);
    ((Rec_func_800206D0_arg1 *)motion)->unk_00 += ((Rec_func_800206D0_arg1 *)motion)->unk_0C;
    ((Rec_func_800206D0_arg1 *)motion)->unk_04 += ((Rec_func_800206D0_arg1 *)motion)->unk_10;
    ((Rec_func_800206D0_arg1 *)motion)->unk_08 += ((Rec_func_800206D0_arg1 *)motion)->unk_14;
    ((Rec_func_800206D0_arg1 *)motion)->unk_14 += 0x30000;
    timer = --((S_800206D0_0 *)pickup)->unk_02.s;
    if ((s16)timer > 0) {
        goto end;
    }
    func_80053DA8(0x501);
    ((Rec_func_800206D0_arg1 *)motion)->unk_08 = 0xFFC00000;
    ((Rec_func_800206D0_arg1 *)motion)->unk_14 = ((rand() & 0xFF) << 11) + 0xFFE80000;
    ((S_800206D0_0 *)pickup)->unk_02.u = (rand() & 0xF) + 30;
    ((S_800206D0_0 *)pickup)->unk_00 = 3;
    goto end;

state3:
    {
        s32 floor_z = 0xFFC00000;
        s32 idle_frame;

        func_800478B8(sprite);
        ((Rec_func_800206D0_arg1 *)motion)->unk_08 += ((Rec_func_800206D0_arg1 *)motion)->unk_14;
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 += 0x30000;
        if (floor_z < ((Rec_func_800206D0_arg1 *)motion)->unk_08) {
            func_80053DA8(0x501);
            ((Rec_func_800206D0_arg1 *)motion)->unk_08 = floor_z;
            ((Rec_func_800206D0_arg1 *)motion)->unk_14 = -((Rec_func_800206D0_arg1 *)motion)->unk_14 >> 1;
        }
        if (func_8008FD9C(D_80024420, motion, &D_800D0420, D_80083780) != 0) {
            func_80053DA8(0x516);
            reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
            D_80012D5C[0] += reward;
            D_80024628[0] += reward;
            ((S_800206D0_0 *)pickup)->unk_00 = 6;
        }
        timer = --((S_800206D0_0 *)pickup)->unk_02.s;
        if ((s16)timer > 0) {
            goto end;
        }
        ((S_800206D0_0 *)pickup)->unk_02.u = 180;
        ((S_800206D0_0 *)pickup)->unk_00 = 4;
        idle_frame = D_8002445C[((S_800206D0_0 *)pickup)->unk_54];
        ((S_800206D0_2 *)sprite)->unk_12.u = 0;
        ((S_800206D0_2 *)sprite)->unk_04 = 0;
        ((S_800206D0_2 *)sprite)->unk_05 = 0;
        ((S_800206D0_2 *)sprite)->unk_08 = idle_frame;
        ((Rec_func_800206D0_arg1 *)motion)->unk_08 = floor_z;
        goto end;
    }

state4:
    if (func_8008FD9C(D_80024420, motion, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
        D_80012D5C[0] += reward;
        D_80024628[0] += reward;
        ((S_800206D0_0 *)pickup)->unk_00 = 6;
    }
    timer = --((S_800206D0_0 *)pickup)->unk_02.s;
    if ((s16)timer > 0) {
        goto end;
    }
    ((S_800206D0_0 *)pickup)->unk_02.u = 31;
    ((S_800206D0_0 *)pickup)->unk_00 = 5;
    goto end;

state5:
    if ((((S_800206D0_0 *)pickup)->unk_02.s >> 2) & 1) {
        ((S_800206D0_2 *)sprite)->unk_14 |= 0x80;
    } else {
        ((S_800206D0_2 *)sprite)->unk_14 &= 0xFF7F;
    }
    if (func_8008FD9C(D_80024420, motion, &D_800D0420, D_80083780) != 0) {
        func_80053DA8(0x516);
        reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
        D_80012D5C[0] += reward;
        D_80024628[0] += reward;
        ((S_800206D0_0 *)pickup)->unk_00 = 6;
    }
    timer = --((S_800206D0_0 *)pickup)->unk_02.s;
    if ((s16)timer > 0) {
        goto end;
    }
    ((S_800206D0_0 *)pickup)->unk_00 = 6;
    goto end;

state6:
    func_8008F134((u8 *)pickup + 8);
    (*(u16 *)((u8 *)pickup + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
