#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A5DFC(void *, void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170F20[];
extern u8 D_801762D8[];
extern u8 D_801762E0[];

void func_801721B0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 temp_delta;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    u8 *global;

    temp_v1 = FIELD(arg0, u8, 0x9B);
    if (temp_v1 == 1) {
        goto state_one;
    }
    if (temp_v1 >= 2) {
        goto check_state_two;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto common_update;

check_state_two:
    if (temp_v1 == 2) {
        goto state_two;
    }
    goto common_update;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, void *, 0x2C) = D_801762D8;
        func_80047784(
            arg2,
            D_801762D8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >>
                         9) &
                        7],
            0);
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s16, 0x9E) = 5;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;
        goto state_one;
    }
    goto common_update;

state_one:
    temp_a0 = FIELD(arg0, s16, 0x9E);
    FIELD(arg0, s32, 0x90) =
        FIELD(arg0, s32, 0x90) - FIELD(arg0, s32, 0xA0);
    if (temp_a0 != 0) {
        FIELD(arg1, s32, 0xC) =
            (((FIELD(arg2, u8, 0x24) << 6) -
              ({ FIELD(arg1, s16, 2) - 0x20; })) <<
             0x10) /
            temp_a0;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) -
              (temp_delta = FIELD(arg1, s16, 6) - 0x20)) <<
             0x10) /
            FIELD(arg0, s16, 0x9E);
        FIELD(arg0, s32, 0xA0) =
            (-func_800644B8(FIELD(arg0, s16, 0x9E) * 0x199)) << 9;
    }
    FIELD(arg0, s32, 0x90) =
        FIELD(arg0, s32, 0x90) + FIELD(arg0, s32, 0xA0);
    temp_v1_2 = FIELD(arg0, u16, 0x9E) - 1;
    FIELD(arg0, s16, 0x9E) = temp_v1_2;
    if ((s16)temp_v1_2 < 0) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, s32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

state_two:
    if (FIELD(arg3, s32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                     FIELD(arg2, u8, 0x25));
        FIELD(arg2, void *, 0x2C) = D_801762E0;
        func_80047784(
            arg2,
            D_801762E0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >>
                         9) &
                        7],
            0);
        FIELD(arg0, u8, 0x9B)++;
    }

common_update:
    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                     FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        global = (u8 *)&D_80083460;
        if (FIELD(global, s16, 8) != 0) {
            FIELD(global, s16, 8) = (u16)FIELD(global, s16, 8) - 1;
        }
        temp_v1_3 = FIELD(arg3, s32, 0x1C);
        if (temp_v1_3 & 0x2000) {
            u16 temp_flags;

            temp_flags = FIELD(arg3, u16, 0x46);
            if (temp_flags & 0x8000) {
                FIELD(arg3, u16, 0x46) = temp_flags & 0x7FFF;
            }
            goto coordinate_done;
        }
        if (temp_v1_3 & 0x410) {
            goto coordinate_done;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto coordinate_done;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);

coordinate_done:
        func_800A5DFC(arg3, arg1);
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            FIELD(arg0, void *, 0x8C) = D_80170F20;
            func_800A9A04(arg3);
        }
    }
}
