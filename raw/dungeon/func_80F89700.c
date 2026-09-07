#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];

void func_80172F00(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer_signed;
    s32 index;
    s32 x;
    s32 y;
    s32 rounded_x;
    s32 rounded_y;
    s32 value;
    s32 *global_state;
    s32 state;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    index = (FIELD(arg3, u16, 0x6A) >> 9) & 7;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
            func_800AD4D0(arg3);
            if (FIELD(arg3, u8, 0x28) == 0) {
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(arg1, s32, 0x10) = 0;
                FIELD(arg1, s32, 0xC) = 0;
                FIELD(arg1, s32, 0x14) = 0xFFFD0000;
                func_800AAA54(arg0, arg1, arg2, D_80174ADC);
                return;
            }

            {
                u32 mask_a0 = 0xF7FFFFFF;
                u32 mask_v1 = 0xFFFBFFFF;
                u32 flags;
                u16 field98;

                FIELD(arg1, s32, 0xC) =
                    ((s16 *)&D_8006CCD8)[index] << 18;
                FIELD(arg1, s32, 0x10) =
                    ((s16 *)&D_8006CCE8)[index] << 18;
                FIELD(arg1, s32, 0x14) = 0x20000;

                field98 = FIELD(arg0, u16, 0x98);
                field98 |= 8;
                FIELD(arg0, u16, 0x98) = field98;
                flags = FIELD(arg3, u32, 0x1C);
                flags &= mask_a0;
                flags &= mask_v1;
                FIELD(arg3, u32, 0x1C) = flags;
            }

            FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
            timer_signed = -1;
            if (FIELD(arg3, u32, 0x1C) & 0x228) {
                timer_signed = 8;
            }
            FIELD(arg0, s16, 0x96) = timer_signed;

            x = FIELD(arg1, s32, 0xC);
            rounded_x = x;
            if (x < 0) {
                rounded_x = x + 3;
            }
            y = FIELD(arg1, s32, 0x10);
            FIELD(arg1, s32, 0xC) = x - (rounded_x >> 2);
            rounded_y = y;
            if (y < 0) {
                rounded_y = y + 3;
            }
            FIELD(arg1, s32, 0x10) = y - (rounded_y >> 2);
            return;

state_1:
    FIELD(arg1, s32, 0xC) -=
        ((s16 *)&D_8006CCD8)[index] << 15;
    FIELD(arg1, s32, 0x10) -= ((s16 *)&D_8006CCE8)[index] << 15;

    timer_signed = FIELD(arg0, s16, 0x96);
    timer = FIELD(arg0, volatile u16, 0x96);
    if (timer_signed > 0) {
        timer -= 1;
        FIELD(arg0, u16, 0x96) = timer;
        goto check_timer;
    }
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, u16, 0x96) = 0;
    }

check_timer:
    if (FIELD(arg0, s16, 0x96) != 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto increment_state;
    }

start_action:
    FIELD(arg0, u8, 0x9B) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg1, s32, 0x14) = 0xFFFD0000;
    func_800AAA54(arg0, arg1, arg2, D_80174ADC);
    return;

increment_state:
    FIELD(arg0, s16, 0x96) = 5;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    return;

state_2:
    FIELD(arg1, s32, 0x14) = 0xFFFD0000;
    if (FIELD(arg0, s16, 0x96) != 0) {
        s32 scaled;
        s32 origin;

        scaled = FIELD(arg2, u8, 0x24) << 6;
        origin = FIELD(arg1, s16, 2);
        origin -= 0x20;
        FIELD(arg1, s32, 0xC) = (scaled - origin) << 15;
        scaled = FIELD(arg2, u8, 0x25) << 6;
        origin = FIELD(arg1, s16, 6);
        origin -= 0x20;
        FIELD(arg1, s32, 0x10) = (scaled - origin) << 15;
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;
    FIELD(arg3, u32, 0x1C) |= 0x00040000;
    FIELD(arg2, u8 *, 0x2C) = D_80174AD4;
    func_80047784(
        arg2,
        D_80174AD4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);

    global_state = &D_80083460;
    value = global_state[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        global_state[4] = value & 0x7FFFFFFF;
    }
    FIELD(arg0, u8 *, 0x8C) = D_80171138;
}

/* MECHANISM: Symbolic s16 indexing and C/10/14 store order reproduce both table-load regions.
   Block-scoped scaled/origin temporaries preserve the two addiu-before-subu sequences
   without extending the earlier rounding temporaries across the state-machine CFG. */
