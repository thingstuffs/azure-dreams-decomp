#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8008B9FC_1 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008B9FC_1;   /* arg0 in func_8008B9FC */


typedef struct S_8008B9FC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_8008B9FC_3;   /* state in func_8008B9FC */

typedef struct S_8008B9FC_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008B9FC_4;   /* tail_word_obj in func_8008B9FC */

typedef struct S_8008B9FC_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_5;   /* callback_obj in func_8008B9FC */

typedef struct S_8008B9FC_6 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_6;   /* callback_obj_f0 in func_8008B9FC */

typedef struct S_8008B9FC_7_pre {
    s16 unk_00;
    u8 pad_02[0x23A];
} S_8008B9FC_7_pre;   /* the 0x23C bytes before D_80083464 in func_8008B9FC, addressed as D_80083464[-1] */



extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern volatile u16 D_80013714[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u16 D_80083460[];
extern s16 D_80083464[];
extern u8 D_800DCFB0[];
extern u8 D_800DCFB8[];
extern u8 D_800DCFC0[];
extern u8 D_800DCFE8[];
extern u8 D_800DD030[];
extern u8 D_800DD0D0[];
extern u8 D_800E3544[];

extern void D_8008ACDC(void);
extern void func_80048A44();
extern void func_8008CD4C();
extern void func_8008E264();
extern void func_80094ED4();
extern void func_80099F04();
extern void func_80099F70();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s16 func_8009ABA0();
extern void func_8009F644();
extern s32 func_800A5C70();
extern void func_800A67F4();

void func_8008B9FC(S_8008B9FC_1 *arg0, s32 arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    u8 *state = D_80083160;
    u8 *alt_callback;
    u16 *flags;
    u16 *check_flags;
    s16 temp_v0;
    u16 index;
    register s32 mask ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 flag_word;
    u16 temp_v0_2;

    temp_v0 = func_8009ABA0(arg3->unk_2A.as_s16, arg1, arg2,
                            arg3->unk_88.as_s16, 0x20);
    if (temp_v0 > 0) {
        arg0->unk_9B = 0;
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        index = ((u16)arg3->unk_2A.as_s16 >> 8) & 0xE;
        {
            u8 x = arg2->unk_24;
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x + movement_x[index]);
            arg2->unk_24 = x;
        }
        arg2->unk_25 =
            (u8)(arg2->unk_25 + D_8006CCE8[index]);
        func_8009A21C(arg2->unk_24, arg2->unk_25, 0x300);
        flags = D_80083460;
        flags[1] |= 8;
        arg0->unk_8C.s = 0;

        if (temp_v0 != 4) {
            if ((D_80013714[0] & 2) ||
                (((((S_8008B9FC_3 *)state)->unk_08 & 0x20) != 0) &&
                 ((arg0->unk_A2 & 0x100) == 0) &&
                 func_800A5C70())) {
                flags[1] |= 0x80;
                if (arg2->unk_2C.as_pu8 != D_800DCFC0) {
                    arg2->unk_2C.as_pu8 = D_800DCFC0;
                    func_80048A44(
                        arg2,
                        D_800DCFC0[((s32)(((S_8008B9FC_3 *)state)->unk_C8 +
                                         arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
        }

        check_flags = D_80083460;
        if ((check_flags[1] & 0x80) || (temp_v0 == 1)) {
            func_80099F70(arg3->unk_5C);
            func_80099F04(arg3->unk_5C);
            if (!(check_flags[1] & 0x80) &&
                ((D_800E3544[0] == 8) || (D_800E3544[0] == 0))) {
                if (arg2->unk_2C.as_pu8 != D_800DCFB8) {
                    void *callback_call;
                    callback_call = arg2;
                    ASM_KEEP(callback_call);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    arg2->unk_2C.as_pu8 = D_800DCFB8;
                    func_80048A44(
                        callback_call,
                        D_800DCFB8[((s32)(D_80083228[0] +
                                         arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
            arg0->unk_9A = 0xF;
            D_80083464[0] = 8;
            goto block_80086620;
        }

        arg0->unk_98 |= 0xC;
        if (temp_v0 < 4) {
            arg0->unk_A2 |= 1;
        } else if ((temp_v0 == 2) || (temp_v0 == 4)) {
            arg0->unk_9B = 8;
        }
        func_80094ED4(arg0, arg1, arg2, arg3);
        D_80083464[0] = 8;
        if (arg2->unk_2C.as_pu8 == D_800DCFB8) {
            arg2->unk_14.at00_u16.v |= 0x6000;
            func_8008E264(arg0, arg1, arg2, arg3);
        } else {
            arg2->unk_2C.as_pu8 = D_800DD030;
            func_80048A44(
                arg2,
                D_800DD030[((s32)(D_80083228[0] + arg3->unk_2A.as_s16 +
                                  0x100) >> 9) & 7],
                0, 1);
        }
        arg0->unk_9A = 0x10;
        {
            register void *tail_word_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            tail_word_obj = arg3;
            ((S_8008B9FC_4 *)tail_word_obj)->unk_1C |= 0x40000000;
        }
        func_8009F644(arg3, 8, 0, 0);
        return;

block_80086620:
        func_8009F644(arg3, 8, 0, 0);
        mask = 0x40000000;
        goto block_80086704;
    }

    if (temp_v0 < 0) {
        if ((D_80013714[0] & 1) ||
            (temp_v0_2 = arg0->unk_96 + 1,
             arg0->unk_96 = temp_v0_2,
             (s16)temp_v0_2 >= 0x15)) {
            func_8008CD4C(arg0, arg1, arg2, arg3, (s32)temp_v0);
            if (arg0->unk_9B >= 0x10) {
                arg3->unk_1C.as_s32 |= 0x40000000;
                return;
            }
        }
        return;
    }

    {
        register void *callback_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        callback_obj = arg2;
        ((S_8008B9FC_5 *)callback_obj)->unk_2C = D_800DCFB0;
        func_80048A44(
            callback_obj,
            D_800DCFB0[((s32)(((S_8008B9FC_3 *)state)->unk_C8 +
                              arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0, 1);
    }
    arg0->unk_8C.u = D_8008ACDC;
    return;

block_80086704:
    flag_word = arg3->unk_1C.as_s32 | mask;
    arg3->unk_1C.as_s32 = flag_word;
    ASM_KEEP(flag_word);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    flags = D_80083460;
    flags[1] |= 0x812;
    func_800A67F4();
    func_80094ED4(arg0, arg1, arg2, arg3);
    if (!(D_80013714[0] & 8)) {
        return;
    }

    if (D_800E3544[0] == 0xF0) {
        if (arg2->unk_2C.as_pu8 == D_800DCFC0) {
            goto halve_flags;
        }
        {
            void *callback_obj_f0;
            callback_obj_f0 = arg2;
            ((S_8008B9FC_6 *)callback_obj_f0)->unk_2C = D_800DCFC0;
            func_80048A44(
                callback_obj_f0,
                *(volatile u8 *)(D_800DCFC0 +
                    (((s32)(((S_8008B9FC_7_pre *)D_80083464)[-1].unk_00 +
                              arg3->unk_2A.as_s16 + 0x100) >> 9) & 7)),
                0, 1);
        }
        ASM_SCHED_BARRIER(); /* MATCH: keep the F0 callback call separate from the F8 arm. */
        goto halve_flags;
    }

    if (D_800E3544[0] == 0xF8) {
        alt_callback = D_800DCFB8 + 8;
        arg0->unk_A2 |= 0x100;
        flags[5]++;
        if (arg2->unk_2C.as_pu8 == alt_callback) {
            goto halve_flags;
        }
        arg2->unk_2C.as_pu8 = alt_callback;
        func_80048A44(
            arg2,
            alt_callback[((s32)(D_80083228[0] + arg3->unk_2A.as_s16 +
                                 0x100) >> 9) & 7],
            0, 1);
        goto halve_flags;
    }

    if (D_800E3544[0] == 0xE8) {
        arg2->unk_2C.as_pu8 = D_800DCFE8;
        func_80048A44(
            arg2,
            D_800DCFE8[((s32)(D_80083228[0] + arg3->unk_2A.as_s16 +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        index = ((u16)arg3->unk_2A.as_s16 >> 8) & 0xE;
        arg2->unk_24 -= ((s16 *)(void *)D_8006CCD8)[index / 2] * 2;
        arg2->unk_25 -= ((s16 *)(void *)D_8006CCE8)[index / 2] * 2;
        func_8009A21C(arg2->unk_24, arg2->unk_25, 0x300);
halve_flags:
        flags[2] = (s16)flags[2] >> 1;
        return;
    }

    if (D_800E3544[0] == 0xE0) {
        arg2->unk_2C.as_pu8 = D_800DD0D0;
        func_80048A44(
            arg2,
            D_800DD0D0[((s32)(D_80083228[0] + arg3->unk_2A.as_s16 +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        index = ((u16)arg3->unk_2A.as_s16 >> 8) & 0xE;
        {
            u8 x = arg2->unk_24;
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x - movement_x[index]);
            arg2->unk_24 = x;
        }
        arg2->unk_25 -= D_8006CCE8[index];
        func_8009A21C(arg2->unk_24, arg2->unk_25, 0x300);
    }
}
