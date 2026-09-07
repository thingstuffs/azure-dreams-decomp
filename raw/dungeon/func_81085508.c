#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800644B8(s32);
extern s32 func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800A44E0(s32, s32, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_80174A6C(void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_8008346C;
extern u8 D_800DDC40[];
extern u8 D_80170838[16];
extern u8 D_80170E94;

void func_80172D08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&state_zero, &&state_one,
                                       &&state_two, &&state_three,
                                       &&state_four };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        return;
    }
    (void)keepalive;
    goto *(((void **)D_80170838)[state]);

state_zero: {
    s32 direction;
    s32 value;

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 4;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        return;
    }

    FIELD(arg0, u8, 0xAF) = 0;
    if (FIELD(arg3, void *, 0x60) == 0) {
        direction = (FIELD(arg3, u16, 0x2A) >> 9) & 7;
        if ((s16)func_800A44E0(FIELD(arg2, u8, 0x24) << 6,
                               FIELD(arg2, u8, 0x25) << 6,
                               FIELD(arg3, s16, 0x88),
                               direction << 9) == 0) {
            value = func_800BCB04(
                (((FIELD(arg2, u8, 0x24) +
                   ((s16 *)&D_8006CCD8)[direction]) << 6) + 0x20) & 0xFFE0,
                (((FIELD(arg2, u8, 0x25) +
                   ((s16 *)&D_8006CCE8)[direction]) << 6) + 0x20) & 0xFFE0,
                (s16)(FIELD(arg3, u16, 0x88) - 0x20));
            if ((u16)(value - FIELD(arg3, u16, 0x88) + 0x3F) >= 0x7F) {
                FIELD(arg0, u8, 0xAF) = 1;
            }
        } else {
            FIELD(arg0, u8, 0xAF) = 1;
        }
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, s16, 0x96) = 6;
    FIELD(arg0, u8, 0x9B)++;
}

state_one: {
    s16 timer;
    s32 direction;

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) != 0) {
        return;
    }

    if (FIELD(arg0, u8, 0xAF) == 0) {
        direction = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
        FIELD(arg1, s32, 0x0C) =
            (((s16 *)&D_8006CCD8)[direction >> 1] << 22) / 8;
        FIELD(arg1, s32, 0x10) =
            (((s16 *)&D_8006CCE8)[direction >> 1] << 22) / 8;
    }
    FIELD(arg0, u16, 0x98) |= 0xC;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    return;
}

state_two: {
    s16 timer;
    s16 next_timer;
    register s32 vertical_out ASM_REG("$2");
    register s32 vertical_step ASM_REG("$3");

    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    timer = FIELD(arg0, s16, 0x96);
    if (timer >= 9) {
        if (FIELD(arg3, void *, 0x60) != 0) {
            register s32 scaled_value ASM_REG("$5");
            register s32 scale ASM_REG("$3");
            register s32 vertical ASM_REG("$3");
            s32 scaled_shifted;
            s32 value;
            void *owner;

            owner = FIELD(arg3, void *, 0x60);
            owner = FIELD(owner, void *, -0x18);
            value = func_800644B8(FIELD(arg0, s16, 0x96) << 7) >> 4;
            scale = D_800DDC40[
                FIELD(FIELD(arg3, void *, 0x60), u8, 0x13)] + 0x20;
            scaled_value = value * scale;
            vertical = (FIELD(owner, s16, 0x0A) - FIELD(arg3, s16, 0x88)) << 13;
            vertical *= 0x11 - FIELD(arg0, s16, 0x96);
            scaled_shifted = scaled_value << 8;
            vertical_out = vertical - scaled_shifted;
            goto store_vertical;
        } else if (FIELD(arg0, u8, 0xAF) != 0) {
            s32 value;

            value = func_800644B8(FIELD(arg0, s16, 0x96) << 7) >> 4;
            FIELD(arg0, s32, 0xA0) = -((value * 3) << 13);
        } else {
            s32 direction;
            s32 scaled_vertical;
            s32 terrain_height;
            register s32 signed_terrain_height ASM_REG("$4");
            s32 value;
            s32 vertical;

            direction = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
            terrain_height = func_800BCB04(
                (((FIELD(arg2, u8, 0x24) +
                   ((s16 *)&D_8006CCD8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (((FIELD(arg2, u8, 0x25) +
                   ((s16 *)&D_8006CCE8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (s16)(FIELD(arg3, u16, 0x88) - 0x20));
            value = func_800644B8(FIELD(arg0, s16, 0x96) << 7);
            signed_terrain_height = terrain_height << 16;
            signed_terrain_height >>= 16;
            vertical = (signed_terrain_height - FIELD(arg3, s16, 0x88)) << 13;
            scaled_vertical = vertical * (0x11 - FIELD(arg0, s16, 0x96));
            value = ((value >> 4) * 3) << 13;
            FIELD(arg0, s32, 0xA0) = scaled_vertical - value;
        }
    } else {
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        vertical_step = 0x40000;
        vertical_out = FIELD(arg0, s32, 0xA0) + vertical_step;
store_vertical:
        FIELD(arg0, s32, 0xA0) = vertical_out;
    }

    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    next_timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next_timer;
    if (next_timer > 0) {
        return;
    }
    func_800A56E0(0x803);
    FIELD(arg0, u8, 0x9B)++;
    return;
}

state_three: {
    s32 direction;

    if (((FIELD(arg2, s8, 4) == 0xC) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        if (func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1) != 0) {
            func_800A56E0(0x809);
            func_80174A6C(arg0, arg1, arg2);
        }
    }

    if (((FIELD(arg2, s8, 4) == 0x14) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        if (FIELD(arg0, u8, 0xAF) == 0) {
            direction = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
            FIELD(arg1, s32, 0x0C) =
                -((((s16 *)&D_8006CCD8)[direction >> 1] << 22) / 8);
            FIELD(arg1, s32, 0x10) =
                -((((s16 *)&D_8006CCE8)[direction >> 1] << 22) / 8);
        }
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
    }
    return;
}

state_four: {
    s16 timer;

    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer >= 0) {
        if (FIELD(arg3, void *, 0x60) != 0) {
            s32 movement;
            s32 random_value;
            s32 scaled_movement;
            void *owner;

            owner = FIELD(arg3, void *, 0x60);
            owner = FIELD(owner, void *, -0x18);
            random_value = func_800644B8(FIELD(arg0, s16, 0x96) << 8);
            movement = FIELD(owner, s16, 0x0A) -
                       D_800DDC40[FIELD(FIELD(arg3, void *, 0x60), u8, 0x13)] -
                       FIELD(arg3, s16, 0x88);
            movement <<= 13;
            scaled_movement = movement * FIELD(arg0, s16, 0x96);
            random_value = (random_value >> 4) << 13;
            FIELD(arg0, s32, 0xA0) = scaled_movement - random_value;
        } else if (FIELD(arg0, u8, 0xAF) != 0) {
            s32 value;

            value = func_800644B8(FIELD(arg0, s16, 0x96) << 8) >> 4;
            FIELD(arg0, s32, 0xA0) =
                -(FIELD(arg0, s16, 0x96) << 19) - (value << 13);
            goto vertical_done;
        } else {
            s32 direction;
            s32 movement;
            s32 random_value;
            s32 scaled_movement;
            s32 terrain_height;
            register s32 signed_terrain_height ASM_REG("$3");
            s32 base_height;

            direction = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
            terrain_height = func_800BCB04(
                (((FIELD(arg2, u8, 0x24) +
                   ((s16 *)&D_8006CCD8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (((FIELD(arg2, u8, 0x25) +
                   ((s16 *)&D_8006CCE8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (s16)(FIELD(arg3, u16, 0x88) - 0x20));
            random_value = func_800644B8(FIELD(arg0, s16, 0x96) << 8);
            signed_terrain_height = terrain_height << 16;
            signed_terrain_height >>= 16;
            base_height = FIELD(arg3, s16, 0x88);
            base_height += 0x40;
            movement = signed_terrain_height - base_height;
            movement <<= 13;
            scaled_movement = movement * FIELD(arg0, s16, 0x96);
            random_value = (random_value >> 4) << 13;
            FIELD(arg0, s32, 0xA0) = scaled_movement - random_value;
        }
    } else {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg0, s32, 0xA0) = 0;
    }

vertical_done:
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 0x200);
        FIELD(arg0, void *, 0x8C) = &D_80170E94;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        func_800A4ACC(arg3);
    }
}
}
