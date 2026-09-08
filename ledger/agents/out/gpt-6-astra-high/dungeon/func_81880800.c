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

/* Updates a moving effect through initialization, travel, spawning, fading, and cleanup. */
void FUNC_81880800_BODY(void *effect, void *motion_data, void *render_part)
{
    u8 *self = (u8 *)effect;
    u8 *motion = (u8 *)motion_data;
    register u8 *part ASM_REG("$19") = (u8 *)render_part;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *owner;
    u8 *owner_base;
    u8 *owner_pos;
    void *target;
    s32 state;
    s16 spawn_height;
    s32 direction_step;
    s32 next_state;
    s32 tile_result;
    u32 height_offset;
    u32 target_z;
    s32 magnitude;
    s32 velocity;
    s32 position;
    register s32 next_velocity ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 over_limit;
    s32 x_pos;
    register s32 x_vel ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 y_pos ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 y_vel;
    s32 z_pos;
    s32 z_delta;
    s32 tile_coord;
    register u8 *spawn_base ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    register u32 tile_x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u32 steps_left;
    register u32 tile_y ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 tile_center_x;
    u32 red;
    u32 green;
    u32 blue;
    u32 base_color;
    u32 texture_config;
    u32 texture_size;
    s16 offset[3];
    s32 texture_params[2];
    static void *const state_labels[] = {
        &&initialize, &&travel, &&spawn, &&fade, &&cleanup, &&finish
    };

    owner = F(self, void *, 0);
    state = F(self, s16, 0xA);
    owner_base = (u8 *)owner - 0x20;
    owner_pos = F(owner_base, void *, 8);
    if ((u32)state >= 18U) {
        goto finish;
    }
    (void)state_labels;
    goto *D_80024008[state];

initialize:
    base_color = 0x00808080;
    texture_config = 0x01000340;
    texture_size = 0x00200020;
    F(part, u32, 0xC) = base_color;
    F(part, u16, 0x1E) = 0x800;
    F(part, u16, 0x1C) = 0x800;
    F(part, void *, 8) = D_800257E8;
    F(self, u16, 0x1A) = (F(owner, u16, 0x2A) >> 9) & 7;
    texture_params[0] = texture_config;
    texture_params[1] = texture_size;
    func_800B835C(D_800257D0, texture_params, 1, 0);
    F(self, u16, 0xA)++;

    if (func_8003DF74(F(F(owner_base, void *, 0xC), void *, 8),
                      F(owner_base, void *, 0xC), offset, 0) == 0) {
        if ((F(F(owner_base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto finish;
        }
    }

    F(motion, u16, 2) = F(owner_pos, u16, 2);
    F(motion, u16, 6) = F(owner_pos, u16, 6);
    if (F(F(owner_base, void *, 0xC), u16, 0x14) & 0x8000) {
        F(motion, u16, 0xA) = F(owner_pos, u16, 0xA) - 0x40;
    } else {
        F(motion, u16, 0xA) = F(owner_pos, u16, 0xA) + offset[2];
    }

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
        void *source_record;
        u8 height_index;
        u8 *height_table;
        u8 tile_offset;
        source_record = F(F(owner, void *, 0x60), void *, -0x18);
        F(self, u16, 0x10) = F(source_record, u16, 2);
        F(self, u16, 0x12) = F(source_record, u16, 6);
        height_table = D_800DDC40;
        height_index = F(F(owner, void *, 0x60), u8, 0x13);
        height_offset = height_table[height_index];
        height_offset += 0x20;
        target_z = F(source_record, u16, 0xA);
        F(self, u16, 0x14) = target_z - height_offset;

        {
            s16 direction;
            direction = F(self, s16, 0x1A);
            source_record = F(owner, void *, -0x14);
            tile_offset = F(source_record, u8, 0x24) + D_8006CCD8[direction];
            F(self, u8, 0x20) = tile_offset;
            F(self, u8, 0x22) = tile_offset;
        }
        {
            s16 direction;
            direction = F(self, s16, 0x1A);
            tile_offset = F(source_record, u8, 0x25) + D_8006CCE8[direction];
            F(self, u8, 0x21) = tile_offset;
            F(self, u8, 0x23) = tile_offset;
        }
        {
            s32 owner_tile;
            register s32 source_tile ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            s32 tile_distance;
            owner_tile = F(owner, s8, 0x72);
            source_tile = F(source_record, u8, 0x24);
            if (owner_tile == source_tile) {
                owner_tile = F(owner, s8, 0x73);
                source_tile = F(source_record, u8, 0x25);
                tile_distance = owner_tile - source_tile;
            } else {
                tile_distance = owner_tile - source_tile;
            }
            if (tile_distance < 0) {
                tile_distance = -tile_distance;
            }
            F(self, u16, 0x18) = tile_distance + 1;
        }
    } else {
        F(self, u16, 0x18) = 8;
        F(self, u16, 0x10) = F(motion, u16, 2);
        F(self, u16, 0x12) = F(motion, u16, 6);
        F(self, u16, 0x14) = F(owner, u16, 0x88) - 0x50;
    }
    direction_step = D_8006CCD8[F(self, s16, 0x1A)];
    F(motion, s16, 0x0E) = direction_step << 3;
    direction_step = D_8006CCE8[F(self, s16, 0x1A)];
    F(motion, s16, 0x12) = direction_step << 3;
    next_state = F(self, u16, 0xA);
    F(self, u16, 0x1C) = 0;
    goto advance_loaded_state;

travel:
    velocity = F(motion, s32, 0x0C);
    position = F(motion, s32, 0);
    next_velocity = velocity;
    ASM_KEEP(next_velocity);   /* MATCH pin: retail register colouring depends on it */
    position += velocity;
    F(motion, s32, 0) = position;
    ASM_KEEP(next_velocity);   /* MATCH pin: retail register colouring depends on it */
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
    ASM_KEEP(next_velocity);   /* MATCH pin: retail register colouring depends on it */
    position += velocity;
    F(motion, s32, 4) = position;
    ASM_KEEP(next_velocity);   /* MATCH pin: retail register colouring depends on it */
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

    tile_coord = F(motion, s16, 2);
    if (tile_coord < 0) {
        tile_coord += 0x3F;
    }
    F(self, s8, 0x20) = tile_coord >> 6;
    tile_coord = F(motion, s16, 6);
    if (tile_coord < 0) {
        tile_coord += 0x3F;
    }
    F(self, s8, 0x21) = tile_coord >> 6;
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
        goto advance_state;
    }

    tile_x = F(self, u8, 0x20);
    steps_left = F(self, u16, 0x18) - 1;
    tile_y = F(self, u8, 0x21);
    F(self, u16, 0x18) = steps_left;
    steps_left <<= 16;
    F(self, u8, 0x22) = tile_x;
    F(self, u8, 0x23) = tile_y;
    if (steps_left != 0) {
        tile_center_x = (((s32)F(self, s8, 0x20) << 6) + 0x20) & 0xFFE0;
        tile_result = func_800A45D8(
            tile_center_x,
            (((s32)F(self, s8, 0x21) << 6) + 0x20) & 0xFFE0,
            F(motion, s16, 0x0A));
        if ((tile_result << 16) == 0) {
            goto finish;
        }
    }
    F(self, u16, 0x0A) = 0x10;
    goto finish;

spawn:
    spawn_base = F(owner, void *, 0x60);
    spawn_height = F(spawn_base, s16, 0x88);
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
    goto finish;

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
advance_state:
    next_state = F(self, u16, 0x0A);
advance_loaded_state:
    F(self, u16, 0x0A) = next_state + 1;
    goto finish;

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
