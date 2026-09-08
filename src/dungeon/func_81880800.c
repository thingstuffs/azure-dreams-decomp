#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *D_80024008[];
extern u8 D_800257D0[];
extern u8 D_800257E8[];
extern u8 D_80045340[];
extern s16 D_800257CE[5];
extern u8 D_800DDC40[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];

extern void func_800B835C(void *, s32 *, s32, s32);
extern void *func_8003DF74(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern void func_80025654(void *, void *);
extern s16 func_8009FCF0(u8, u8, u8, u8);
extern void func_800A56E0(s32);
extern s32 func_800A45D8(s32, s32, s16);
extern void *func_80024968(void *, void *, s16);
extern void func_80025760(void *, u8, void *);

extern void func_800241B0(void) __attribute__((noreturn));
extern void func_80024344(void) __attribute__((noreturn));
extern void func_800246A8(void) __attribute__((noreturn));
extern void func_800246AC(void) __attribute__((noreturn));
extern void func_800246F8(void) __attribute__((noreturn));

#ifdef __mips__
static const u32 func_81880800_prefix[] __asm__("func_81880800")
    __attribute__((section(".text.func_81880800"), aligned(4))) = {
    0x80024050,
    0,
    0x800240B4,
    0x80024128,
    0x80024394,
    0x8002459C,
    0x800245D8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x8002461C,
    0x800246BC,
};
__asm__(".globl func_81880800\n"
        ".size func_81880800, 1832");
#define FUNC_81880800_BODY func_81880850
#else
#define FUNC_81880800_BODY func_81880800
#endif

/* Updates a moving effect through initialization, target tracking, fading, and cleanup. */
void FUNC_81880800_BODY(void *effect_data, void *motion_data, void *part_data)
{
    u8 *self = (u8 *)effect_data;
    u8 *motion = (u8 *)motion_data;
    register u8 *part ASM_REG("$19") = (u8 *)part_data;
    u8 *owner;
    u8 *owner_base;
    u8 *owner_motion;
    void *target;
    s32 state;
    s16 spawn_height;
    s32 direction_step;
    s32 state_step;
    s32 height_result;
    u32 height_offset;
    u32 target_height;
    s32 magnitude;
    s32 velocity;
    s32 position;
    register s32 next_velocity ASM_REG("$4");
    s32 over_limit;
    s32 x_pos;
    register s32 x_vel ASM_REG("$5");
    register s32 y_pos ASM_REG("$3");
    s32 y_vel;
    s32 z_pos;
    s32 z_delta;
    s32 coord;
    register u8 *spawn_target ASM_REG("$7");
    register u32 tile_x ASM_REG("$2");
    u32 steps_left;
    register u32 tile_y ASM_REG("$4");
    s32 cell_center_x;
    u32 red;
    u32 green;
    u32 blue;
    u32 color;
    u32 texture_flags;
    u32 texture_size;
    s32 start_height;
    s16 attach_offset[3];
    s32 texture_init[2];
    static void *const state_labels[] = {
        &&initialize, &&track_target, &&spawn_effect, &&fade, &&cleanup, &&finish
    };

    owner = F(self, void *, 0);
    state = F(self, s16, 0xA);
    owner_base = (u8 *)owner - 0x20;
    owner_motion = F(owner_base, void *, 8);
    if ((u32)state >= 18U) {
        goto finish;
    }
    (void)state_labels;
    goto *D_80024008[state];

initialize:
    color = 0x00808080;
    texture_flags = 0x01000340;
    texture_size = 0x00200020;
    F(part, u32, 0xC) = color;
    F(part, u16, 0x1E) = 0x800;
    F(part, u16, 0x1C) = 0x800;
    F(part, void *, 8) = D_800257E8;
    F(self, u16, 0x1A) = (F(owner, u16, 0x2A) >> 9) & 7;
    texture_init[0] = texture_flags;
    texture_init[1] = texture_size;
    func_800B835C(D_800257D0, texture_init, 1, 0);
    F(self, u16, 0xA)++;

    if (func_8003DF74(F(F(owner_base, void *, 0xC), void *, 8),
                       F(owner_base, void *, 0xC), attach_offset, 0) == 0) {
        if ((F(F(owner_base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto finish;
        }
    }

    F(motion, u16, 2) = F(owner_motion, u16, 2);
    F(motion, u16, 6) = F(owner_motion, u16, 6);
    if (F(F(owner_base, void *, 0xC), u16, 0x14) & 0x8000) {
        start_height = F(owner_motion, u16, 0xA) - 0x40;
        ASM_TAILSLOT_PIN(start_height);
        func_800241B0();
    }
    F(motion, u16, 0xA) = F(owner_motion, u16, 0xA) + attach_offset[2];

    if ((F(F(self, void *, 4), u16, 0) & 0x80) == 0) {
        goto finish;
    }
    if ((F(self, u8, 0x16) & 4) == 0) {
        func_8004491C((u8 *)self - 0x20, &D_80045340);
        F(part, u16, 0x10) = 0x20;
        F(part, u8, 0x0E) = 0x80;
        F(part, u8, 0x0D) = 0x80;
        F(part, u8, 0x0C) = 0x80;
        F(part, u16, 0x14) |= 0xC;
        F(self, u8, 0x16) |= 4;
    }

    if (F(owner, void *, 0x60) != 0) {
        void *source_data;
        u8 target_type;
        u8 *height_table;
        u8 tile_coord;
        source_data = F(F(owner, void *, 0x60), void *, -0x18);
        F(self, u16, 0x10) = F(source_data, u16, 2);
        F(self, u16, 0x12) = F(source_data, u16, 6);
        height_table = D_800DDC40;
        target_type = F(F(owner, void *, 0x60), u8, 0x13);
        height_offset = height_table[target_type];
        height_offset += 0x20;
        target_height = F(source_data, u16, 0xA);
        F(self, u16, 0x14) = target_height - height_offset;

        {
            s16 direction;
            direction = F(self, s16, 0x1A);
            source_data = F(owner, void *, -0x14);
            tile_coord = F(source_data, u8, 0x24) + D_8006CCD8[direction];
            F(self, u8, 0x20) = tile_coord;
            F(self, u8, 0x22) = tile_coord;
        }
        {
            s16 direction;
            direction = F(self, s16, 0x1A);
            tile_coord = F(source_data, u8, 0x25) + D_8006CCE8[direction];
            F(self, u8, 0x21) = tile_coord;
            F(self, u8, 0x23) = tile_coord;
        }
        {
            s32 owner_coord;
            register s32 source_coord ASM_REG("$3");
            s32 tile_distance;
            owner_coord = F(owner, s8, 0x72);
            source_coord = F(source_data, u8, 0x24);
            if (owner_coord == source_coord) {
                owner_coord = F(owner, s8, 0x73);
                source_coord = F(source_data, u8, 0x25);
                tile_distance = owner_coord - source_coord;
            } else {
                tile_distance = owner_coord - source_coord;
            }
            if (tile_distance < 0) {
                tile_distance = -tile_distance;
            }
            F(self, u16, 0x18) = tile_distance + 1;
        }
        func_80024344();
    }

    F(self, u16, 0x18) = 8;
    F(self, u16, 0x10) = F(motion, u16, 2);
    F(self, u16, 0x12) = F(motion, u16, 6);
    F(self, u16, 0x14) = F(owner, u16, 0x88) - 0x50;
    ASM_SCHED_BARRIER();
    direction_step = D_8006CCD8[F(self, s16, 0x1A)];
    F(motion, s16, 0x0E) = direction_step << 3;
    direction_step = D_8006CCE8[F(self, s16, 0x1A)];
    F(motion, s16, 0x12) = direction_step << 3;
    state_step = F(self, u16, 0xA);
    ASM_KEEP(state_step);
    F(self, u16, 0x1C) = 0;
    func_800246AC();

track_target:
    velocity = F(motion, s32, 0x0C);
    position = F(motion, s32, 0);
    next_velocity = velocity;
    ASM_KEEP(next_velocity);
    position += velocity;
    F(motion, s32, 0) = position;
    ASM_KEEP(next_velocity);
    next_velocity += next_velocity >> 4;
    magnitude = next_velocity;
    if (next_velocity < 0) {
        magnitude = -magnitude;
    }
    position = 0x200000;
    over_limit = magnitude > position;
    F(motion, s32, 0x0C) = next_velocity;
    if (over_limit) {
        position = -0x200000;
        if (next_velocity > 0) {
            position = 0x200000;
        }
        F(motion, s32, 0x0C) = position;
    }

    velocity = F(motion, s32, 0x10);
    position = F(motion, s32, 4);
    next_velocity = velocity;
    ASM_KEEP(next_velocity);
    position += velocity;
    F(motion, s32, 4) = position;
    ASM_KEEP(next_velocity);
    next_velocity += next_velocity >> 4;
    magnitude = next_velocity;
    if (next_velocity < 0) {
        magnitude = -magnitude;
    }
    position = 0x200000;
    over_limit = magnitude > position;
    F(motion, s32, 0x10) = next_velocity;
    if (over_limit) {
        position = -0x200000;
        if (next_velocity > 0) {
            position = 0x200000;
        }
        F(motion, s32, 0x10) = position;
    }

    z_delta = F(self, s16, 0x14) << 16;
    z_pos = F(motion, s32, 8);
    z_delta -= z_pos;
    z_delta >>= 3;
    z_pos += z_delta;
    F(motion, s32, 8) = z_pos;
    func_80025654(motion, part);

    coord = F(motion, s16, 2);
    if (coord < 0) {
        coord += 0x3F;
    }
    F(self, s8, 0x20) = coord >> 6;
    coord = F(motion, s16, 6);
    if (coord < 0) {
        coord += 0x3F;
    }
    F(self, s8, 0x21) = coord >> 6;
    if (F(self, s16, 0x22) == F(self, s16, 0x20)) {
        goto finish;
    }

    if (F(owner, void *, 0x60) != 0) {
        if (F(self, s16, 0x28) == 0) {
            if ((s16)func_8009FCF0(F(self, u8, 0x20), F(self, u8, 0x21),
                                    F(owner, u8, 0x72), F(owner, u8, 0x73)) < 5) {
                F(self, s16, 0x28) = 1;
                func_800A56E0(0x300);
            }
        }
    }
    if (F(owner, void *, 0x60) != 0 &&
        F(owner, s16, 0x72) == F(self, s16, 0x20)) {
        F(motion, u16, 2) = F(self, u16, 0x10);
        F(motion, u16, 6) = F(self, u16, 0x12);
        F(motion, u16, 0xA) = F(self, u16, 0x14);
        func_800246A8();
    }

    tile_x = F(self, u8, 0x20);
    steps_left = F(self, u16, 0x18) - 1;
    tile_y = F(self, u8, 0x21);
    F(self, u16, 0x18) = steps_left;
    steps_left <<= 16;
    F(self, u8, 0x22) = tile_x;
    F(self, u8, 0x23) = tile_y;
    if (steps_left != 0) {
        cell_center_x = (((s32)F(self, s8, 0x20) << 6) + 0x20) & 0xFFE0;
        height_result = func_800A45D8(
            cell_center_x,
            (((s32)F(self, s8, 0x21) << 6) + 0x20) & 0xFFE0,
            F(motion, s16, 0x0A));
        if ((height_result << 16) == 0) {
            goto finish;
        }
    }
    F(self, u16, 0x0A) = 0x10;
    func_800246F8();

spawn_effect:
    spawn_target = F(owner, void *, 0x60);
    spawn_height = F(spawn_target, s16, 0x88);
    F(self, void *, 0x0C) = func_80024968(self, motion, spawn_height);
    if (F(self, void *, 0x0C) == 0) {
        goto finish;
    }
    F(part, u16, 0x14) |= 0x80;
    do {
        F(self, u16, 0x0A)++;
    } while (0);
    if ((F(F(self, void *, 0x0C), u16, 0x1E) & 0x8000) == 0) {
        goto finish;
    }
    target = F(owner, void *, 0x60);
    if (target != 0) {
        func_80025760(target, F(self, u8, 9), owner);
    }
    F(self, u16, 0x0A) = 0x11;
    func_800246F8();

fade:
    x_pos = F(motion, s32, 0);
    x_vel = F(motion, s32, 0x0C);
    y_pos = F(motion, s32, 4);
    y_vel = F(motion, s32, 0x10);
    x_pos += x_vel;
    y_pos += y_vel;
    F(motion, s32, 0) = x_pos;
    F(motion, s32, 4) = y_pos;
    z_delta = F(self, s16, 0x14) << 16;
    z_pos = F(motion, s32, 8);
    z_delta -= z_pos;
    z_delta >>= 3;
    z_pos += z_delta;
    F(motion, s32, 8) = z_pos;
    red = F(part, u8, 0x0C);
    green = F(part, u8, 0x0D);
    blue = F(part, u8, 0x0E);
    F(part, u8, 0x0C) = red - (red >> 1);
    F(part, u8, 0x0D) = green - (green >> 1);
    F(part, u8, 0x0E) = blue - (blue >> 1);
    func_80025654(motion, part);
    if (F(part, u8, 0x0C) >= 2) {
        goto finish;
    }
    F(self, u16, 0x0A)++;
    func_800246F8();

cleanup:
    if (D_800257CE[0] != 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    F(self, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

finish:
    D_800257CE[0] = 0;
}
