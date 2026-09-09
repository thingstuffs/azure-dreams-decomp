#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800206D0_arg1.h"


typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;



typedef struct S_800236BC_1 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x15];
    u8 unk_1D;
    u8 pad_1E[0x36];
    s16 unk_54;
} S_800236BC_1;   /* arg0 in func_800236BC */


typedef struct S_800236BC_3 {
    u8 pad_00[0x62];
    u16 unk_62;
} S_800236BC_3;   /* ((S_800236BC_1 *)arg0)->unk_00 in func_800236BC */


extern void func_800478B8(void *);
extern void SD_Call(s32);
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
    s32 tail_value;
    register u32 page ASM_REG("$4"); /* MATCH: both reward paths carry the global page in a0. */
    s32 *localp = (s32 *)&local;
    u32 speculative_page;

    ((Rec_func_800206D0_arg1 *)arg1)->unk_00 += ((Rec_func_800206D0_arg1 *)arg1)->unk_0C;
    ((Rec_func_800206D0_arg1 *)arg1)->unk_04 += ((Rec_func_800206D0_arg1 *)arg1)->unk_10;
    ((Rec_func_800206D0_arg1 *)arg1)->unk_08 += ((Rec_func_800206D0_arg1 *)arg1)->unk_14;
    ((S_800236BC_3 *)(((S_800236BC_1 *)arg0)->unk_00))->unk_62 |= 2;

    state = ((S_800236BC_1 *)arg0)->unk_04.s;
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
        return;
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
    return;

state_0:
        func_800478B8(arg2);
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 += 0x40000;
        ((S_800236BC_1 *)arg0)->unk_1D = 0;
        if (((Rec_func_800206D0_arg1 *)arg1)->unk_08 < 0) {
            return;
        }
        SD_Call(0x501);
        ((Rec_func_800206D0_arg1 *)arg1)->unk_08 = 0;
        ((S_800236BC_1 *)arg0)->unk_06.s = 15;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_0C = ((rand() % 320) - 64) << 12;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_10 = (rand() % 96 + 128) << 12;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 = 0xFFF00000;
        ((S_800236BC_1 *)arg0)->unk_04.u++;
        return;

state_1:
        func_800478B8(arg2);
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 += 0x40000;
        ((S_800236BC_1 *)arg0)->unk_06.u--;
        if (((Rec_func_800206D0_arg1 *)arg1)->unk_08 < 0) {
            return;
        }
        SD_Call(0x501);
        if (((S_800236BC_1 *)arg0)->unk_06.s > 0) {
            ((Rec_func_800206D0_arg1 *)arg1)->unk_08 = 0;
            ((Rec_func_800206D0_arg1 *)arg1)->unk_14 = -((Rec_func_800206D0_arg1 *)arg1)->unk_14;
            return;
        }
        ((Rec_func_800206D0_arg1 *)arg1)->unk_08 = 0;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_10 = 0;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_0C = 0;
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 = ((rand() & 0xFF) << 11) - 0x150000;
        ((S_800236BC_1 *)arg0)->unk_06.s = (rand() & 0xF) + 30;
        ((S_800236BC_1 *)arg0)->unk_04.u++;
        return;

state_2:
        func_800478B8(arg2);
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 += 0x30000;
        ((S_800236BC_1 *)arg0)->unk_06.u--;
        speculative_page = 0x80020000;
        if (((Rec_func_800206D0_arg1 *)arg1)->unk_08 < 0) {
            goto state_2_collision;
        }
        ((Rec_func_800206D0_arg1 *)arg1)->unk_08 = 0;
        if (((S_800236BC_1 *)arg0)->unk_06.s < 0) {
            value = D_800244DC[((S_800236BC_1 *)arg0)->unk_54];
            ((Rec_D_80082E80 *)arg2)->unk_12.at00_s16.v = 0;
            ((Rec_D_80082E80 *)arg2)->unk_04.as_u8 = 0;
            ((Rec_D_80082E80 *)arg2)->unk_05.as_u8 = 0;
            ((Rec_D_80082E80 *)arg2)->unk_08 = value;
            ((Rec_func_800206D0_arg1 *)arg1)->unk_14 = 0;
            ((S_800236BC_1 *)arg0)->unk_06.s = 150;
            ((S_800236BC_1 *)arg0)->unk_04.u++;
            goto state_2_collision;
        }
        ((Rec_func_800206D0_arg1 *)arg1)->unk_14 = -((Rec_func_800206D0_arg1 *)arg1)->unk_14 >> 1;
        ASM_KEEP(speculative_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        speculative_page = 0x80020000;
state_2_collision:
        speculative_page += 0x4488;
        if (func_8008FD9C((void *)speculative_page, arg1, &D_800D0420, D_80083780) == 0) {
            return;
        }
        SD_Call(0x516);
        {
            u8 *frame;
            frame = __builtin_alloca(0);
            tail_value = *(s32 *)(((S_800236BC_1 *)arg0)->unk_54 * 4 + frame);
            page = 0x80010000;
            goto collision_reward;
        }

state_3:
        ((S_800236BC_1 *)arg0)->unk_06.u--;
        if (((S_800236BC_1 *)arg0)->unk_06.s < 0) {
            ((S_800236BC_1 *)arg0)->unk_06.s = 31;
            ((S_800236BC_1 *)arg0)->unk_04.u++;
        }
        if (func_8008FD9C(D_80024488, arg1, &D_800D0420, D_80083780) == 0) {
            return;
        }
        SD_Call(0x516);
        tail_value = localp[((S_800236BC_1 *)arg0)->unk_54];
        page = 0x80010000;
collision_reward:
        {
            s32 first, second;
            u32 other_page = 0x80020000;
            ASM_KEEP(other_page); /* MATCH: prepare the second global page before the reward arithmetic. */
            amount = tail_value * 100;
            first = *(s32 *)(page + 0x2D5C);
            second = *(s32 *)(other_page + 0x4628);
            *(s32 *)(page + 0x2D5C) = first + amount;
            *(s32 *)(other_page + 0x4628) = second + amount;
        }
        ((S_800236BC_1 *)arg0)->unk_04.s = 255;
        return;

state_4:
        if (func_8008FD9C(D_80024488, arg1, &D_800D0420, D_80083780) != 0) {
            SD_Call(0x516);
            amount = localp[((S_800236BC_1 *)arg0)->unk_54] * 100;
            D_80012D5C[0] += amount;
            D_80024628[0] += amount;
            ((S_800236BC_1 *)arg0)->unk_04.s = 255;
        }
        {
            s32 tail_value;
            if ((((S_800236BC_1 *)arg0)->unk_06.u >> 2) & 1) {
                tail_value = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x80;
            } else {
                tail_value = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xFF7F;
            }
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = tail_value;
        }
        ((S_800236BC_1 *)arg0)->unk_06.u--;
        if (((S_800236BC_1 *)arg0)->unk_06.s > 0) {
            return;
        }
        ((S_800236BC_1 *)arg0)->unk_04.s = 255;
        return;

state_255:
        func_8008F134((u8 *)arg0 + 8);
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
}
