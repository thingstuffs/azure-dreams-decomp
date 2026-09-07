#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80170870[];
extern u8 D_801755E0[16];
extern s32 D_800814A0;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, u8 *);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_801748B8(void) __attribute__((noreturn));
extern void func_80174AA0(void) __attribute__((noreturn));
extern void func_80174C5C(void) __attribute__((noreturn));

void func_801747F0(void *arg0, void *arg1, void *arg2)
{
    static void *const jump_targets[] = { &&jt0, &&jt1, &&jt2, &&jt3, &&jt4 };
    u8 colors[4];
    s32 old_height;
    s32 old_height2;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 y_cell;
    u16 count;
    s16 count_after;
    u16 next_z;
    u16 z;
    u32 distance;
    u8 *tile;
    u8 *tile_base;
    s32 step;
    s32 target_y;
    s32 tile_x;
    s32 tile_y;

state1:
    if (FIELD(arg0, s16, 0x1C) != 1) {
        goto state2;
    }
    if (FIELD(arg0, s16, 0x1E) != 0) {
        goto move1;
    }
    FIELD(arg0, u16, 0x1E) = (u16)(FIELD(arg0, u16, 0x1E) + 1);
    y_cell = FIELD(arg0, s8, 0x51);
    dx = FIELD(arg1, s16, 0xE) - FIELD(arg0, s8, 0x50);
    target_y = FIELD(arg1, s16, 0x12);
    if (dx < 0) {
        dx = -dx;
    }
    dy = target_y - y_cell;
    if (dy < 0) {
        dy = -dy;
    }
    distance = dx + dy;
    if (distance >= 5U) {
        goto far1;
    }
    (void)jump_targets;
    goto *D_80170870[distance];
jt0:
    {
        register s32 result ASM_REG("$2") = 4;
        ASM_TAILSLOT_PIN(result);
        func_801748B8();
        return;
    }
jt1:
    {
        register s32 result ASM_REG("$2") = 8;
        ASM_TAILSLOT_PIN(result);
        func_801748B8();
        return;
    }
jt2:
    {
        register s32 result ASM_REG("$2") = 0xC;
        ASM_TAILSLOT_PIN(result);
        func_801748B8();
        return;
    }
jt3:
    {
        register s32 result ASM_REG("$2") = 0xE;
        ASM_TAILSLOT_PIN(result);
        func_801748B8();
        return;
    }
jt4:
far1:
    FIELD(arg0, u16, 0x26) = 0x10;
move1:
    count_after = FIELD(arg0, u16, 0x26) - 1;
    FIELD(arg0, u16, 0x26) = count_after;
    if (count_after != 0) {
        s32 next_x;
        s32 next_target_y;
        {
            register s32 interp_target ASM_REG("$3");
            register s32 interp_current ASM_REG("$2");
            interp_target = FIELD(arg1, s16, 0xE) << 6;
            interp_current = FIELD(arg1, s16, 2) - 0x20;
            interp_target -= interp_current;
            interp_target /= count_after;
            next_x = (u16)FIELD(arg1, s16, 2) + interp_target;
            ASM_KEEP(interp_target);
            next_target_y = FIELD(arg1, s16, 0x12);
            FIELD(arg1, s16, 2) = next_x;
        }
        {
            register s32 interp_target_y ASM_REG("$3");
            s32 interp_current_y;
            interp_target_y = next_target_y << 6;
            interp_current_y = FIELD(arg1, s16, 6) - 0x20;
            interp_target_y -= interp_current_y;
            interp_target_y /= FIELD(arg0, s16, 0x26);
            FIELD(arg1, s16, 6) = (u16)FIELD(arg1, s16, 6) + interp_target_y;
        }
        FIELD(arg1, s16, 0xA) = (u16)FIELD(arg1, s16, 0xA) +
            ((FIELD(arg1, s16, 0x16) - FIELD(arg1, s16, 0xA)) /
             FIELD(arg0, s16, 0x26));
    }
    if (FIELD(arg0, s16, 0x26) <= 0) {
        colors[0] = FIELD(arg0, u8, 0x2C);
        colors[1] = FIELD(arg0, u8, 0x2D);
        colors[2] = FIELD(arg0, u8, 0x2E);
        colors[3] = FIELD(arg0, u8, 0x2F);
        func_800A7A7C(FIELD(arg1, s16, 0xE), FIELD(arg1, s16, 0x12),
                      FIELD(arg1, s16, 0x16), FIELD(arg2, s32, 8), colors);
        func_80174AA0();
        return;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state1;
    }

state2:
    if (FIELD(arg0, s16, 0x1C) != 2) {
        goto state0;
    }
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x5C);
    FIELD(arg0, s32, 0x5C) += FIELD(arg0, s32, 0x68);
    next_z = FIELD(arg2, u16, 0x1E) - 0xC8;
    FIELD(arg2, u16, 0x1E) = next_z;
    FIELD(arg2, u16, 0x1C) = next_z;
    {
        register s32 state2_x ASM_REG("$4");
        register s32 state2_y ASM_REG("$5");
        state2_x = FIELD(arg0, s8, 0x50);
        state2_y = FIELD(arg0, s8, 0x51);
        z = FIELD(arg1, volatile u16, 0xA);
        old_height = FIELD(arg1, s16, 0xA);
        if ((func_800BCB04((state2_x << 6) & 0xFFC0,
                           (state2_y << 6) & 0xFFC0,
                           (s16)(z - 0x20)) - 7) < old_height) {
            FIELD(arg1, s16, 0xA) = func_800BCB04(
                (FIELD(arg0, s8, 0x50) << 6) & 0xFFC0,
                (FIELD(arg0, s8, 0x51) << 6) & 0xFFC0,
                (s16)(FIELD(arg1, u16, 0xA) - 0x20));
            FIELD(arg1, s16, 8) = 0;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            return;
        }
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state2;
    }

state0:
    if (FIELD(arg0, s16, 0x1C) != 0) {
        return;
    }
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x54);
    FIELD(arg0, s32, 0x54) += FIELD(arg0, s32, 0x60);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x58);
    {
        register s32 current_y ASM_REG("$2");
        register s32 accel_y ASM_REG("$3");
        current_y = FIELD(arg0, s32, 0x58);
        accel_y = FIELD(arg0, s32, 0x64);
        ASM_SCHED_BARRIER();
        current_y += accel_y;
        tile_base = D_801755E0;
        ASM_USE(tile_base);
        FIELD(arg0, s32, 0x58) = current_y;
        ASM_SCHED_BARRIER();
    }
    tile = (FIELD(arg0, s16, 0x24) * 4) + tile_base;
    tile_x = FIELD(arg0, s8, 0x50) + FIELD(tile, s16, 0);
    x = FIELD(arg1, s16, 2);
    if (x < 0) {
        x += 0x3F;
    }
    if (tile_x == (x >> 6)) {
        tile_y = FIELD(arg0, s8, 0x51) + FIELD(tile, s16, 2);
        y = FIELD(arg1, s16, 6);
        if (y < 0) {
            y += 0x3F;
        }
        if (tile_y == (y >> 6)) {
            if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                               FIELD(arg1, s16, 0xA)) << 16) != 0) {
                goto blocked;
            }
            if (func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                              FIELD(arg1, s16, 0xA)) >= 0x200) {
blocked:
                FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x54);
                FIELD(arg0, s32, 0x54) = 0;
                FIELD(arg0, s32, 0x60) = 0;
                FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x58);
                FIELD(arg0, s32, 0x58) = 0;
                FIELD(arg0, s32, 0x64) = 0;
                func_80174C5C();
                return;
            }
            FIELD(arg0, u8, 0x50) += *(u8 *)((FIELD(arg0, s16, 0x24) * 4) + tile_base);
            FIELD(arg0, u8, 0x51) += *(u8 *)((FIELD(arg0, s16, 0x24) * 4) + tile_base + 2);
            FIELD(arg2, s16, 6) = 0;
        }
    }
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x5C);
    FIELD(arg0, s32, 0x5C) += FIELD(arg0, s32, 0x68);
    z = FIELD(arg1, volatile u16, 0xA);
    old_height2 = FIELD(arg1, s16, 0xA);
    if ((func_800BCB04((FIELD(arg0, s8, 0x50) << 6) & 0xFFC0,
                       (FIELD(arg0, s8, 0x51) << 6) & 0xFFC0,
                       (s16)(z - 0x20)) - 0x10) < old_height2) {
        FIELD(arg1, s16, 0xA) = func_800BCB04(
            (FIELD(arg0, s8, 0x50) << 6) & 0xFFC0,
            (FIELD(arg0, s8, 0x51) << 6) & 0xFFC0,
            (s16)(FIELD(arg1, u16, 0xA) - 0x20));
        FIELD(arg1, s16, 8) = 0;
        FIELD(arg0, s32, 0x64) = 0;
        FIELD(arg0, s32, 0x58) = 0;
        FIELD(arg0, s32, 0x60) = 0;
        FIELD(arg0, s32, 0x54) = 0;
        FIELD(arg0, u16, 0x1C) = FIELD(arg0, u16, 0x1C) + 1;
        if ((func_800A7234(FIELD(arg0, s8, 0x50), FIELD(arg0, s8, 0x51),
                           (s16)(FIELD(arg1, u16, 0xA) - 0x20),
                           (s16 *)((u8 *)arg1 + 0xE),
                           (s16 *)((u8 *)arg1 + 0x12),
                           (s16 *)((u8 *)arg1 + 0x16)) << 16) == 0) {
            FIELD(arg0, s16, 0x1C) = 2;
            FIELD(arg0, s32, 0x5C) = 0xFFF80000;
        }
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state0;
    }
}
