#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u16 x;
    u16 y;
} PathPoint;

typedef struct {
    PathPoint point[8];
} PathTable;

extern void func_80047784(void *, u8, s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170838[16];
extern s32 D_80170E84;
extern u8 D_80174820[];

void func_80172288(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3)
{
    PathTable path;
    s32 result;
    s32 duration;
    s32 coordinate;
    s16 timer;
    s32 flags;
    s32 state;
    u8 counter_value;
    u8 *counter;

    path = *(PathTable *)D_80170838;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement;
    }
    if (state == 2) {
        goto state_two;
    }
    goto decrement;

state_zero:
    if (FIELD(arg0, s16, 0x96) < 8) {
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg1, s32, 0x14) = 0xFFEE0000;
        FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
        counter_value = *(volatile u8 *)(arg0 + 0x9B);
        FIELD(arg0, s32, 0xA0) = 0;
        goto increment_state;
    }
    goto decrement;

state_one:
    duration = FIELD(arg0, s16, 0x96);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    if (duration != 0) {
        {
            s32 pixel;
            s32 origin;

            pixel = arg2[0x24];
            origin = FIELD(arg1, s16, 2);
            pixel <<= 6;
            origin -= 0x20;
            FIELD(arg1, s32, 0x0C) =
                ((pixel - origin) << 16) / duration;
        }
        coordinate = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            (((arg2[0x25] << 6) - coordinate) << 16) /
            FIELD(arg0, s16, 0x96);
        FIELD(arg0, s32, 0xA0) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x40000;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    if (FIELD(arg0, s16, 0x96) < 3) {
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
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, arg2[0x24], arg2[0x25]);
        FIELD(arg2, u8 *, 0x2C) = D_80174820;
        func_80047784(
            arg2,
            D_80174820[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        counter_value = FIELD(arg0, u8, 0x9B);
increment_state:
        FIELD(arg0, u8, 0x9B) = counter_value + 1;
    }

decrement:
    timer = FIELD(arg0, s16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = timer;
    if ((timer << 16) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, arg2[0x24], arg2[0x25]);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        counter = (u8 *)&D_80083460;
        if (FIELD(counter, s16, 8) != 0) {
            FIELD(counter, u16, 8)--;
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
                goto update_actor;
            }
            goto update_actor;
        }
        if (flags & 0x410) {
            goto update_actor;
        }
        if (!(flags & 0x20000)) {
            goto update_actor;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            arg2[0x24], arg2[0x25], D_80082E80[0x24], D_80082E80[0x25],
            &result);

update_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, s32 *, 0x8C) = &D_80170E84;
            func_800A9A04(arg3);
            goto update_position;
        }
    } else {
update_position:
        FIELD(arg2, u16, 0x1C) = path.point[FIELD(arg0, s16, 0x96)].x;
        FIELD(arg2, u16, 0x1E) = path.point[FIELD(arg0, s16, 0x96)].y;
    }
}

/* MECHANISM: The 32-byte PathTable copy fixes the 0x58 frame and stack slots.
   Block-scoped pixel/origin ranges force retail's lbu/lh/sll/addiu order.
   A dedicated u8 counter merges both predecessors at the load-delay nop. */
