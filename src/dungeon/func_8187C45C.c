#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct { u8 b[12]; } AggU12;
extern u8 D_80080000[];

typedef struct {
    s16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    Point p[8];
} PointTable __attribute__((packed));

typedef struct {
    u32 w[3];
} Copy12 __attribute__((packed));

typedef struct {
    u8 pad[0x98];
    Copy12 copy;
} PackedArg0 __attribute__((packed));

typedef struct {
    u8 pad[0x64];
    Copy12 copy;
} PackedSpawn __attribute__((packed));

extern PointTable D_80024074;
extern Copy12 D_80026934;
extern Copy12 D_80026940;
extern s16 D_8002694C[5];
extern u8 D_8007CCD8[];
extern u8 D_8007CCE8[];
extern u8 D_800DDC40[];
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void *func_8003FC64(s32);
extern s32 func_80069EF8(void);
extern void func_800250B0(void *, s32, u32, u32, s32, s32, s32);
extern void func_800251E8(s32, u32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800240B8(void *, u8, void *);
extern void func_800A56E0(s32);
extern void *memcpy(void *, const void *, unsigned int);

extern void func_80045340(void);
extern void func_8002569C(void);
extern void func_800257E0(void);

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/* Update a projectile effect, its trail, and the target hit animation. */
void func_80025C5C(void *effect, void *motion, void *sprite) {
    u16 origin_offset[4];
    PointTable direction_steps;
    void *owner;
    void *object;
    void *object_data;
    void *effect_object;
    void *owner_sprite;
    void *origin_sprite;
    void *target_data;
    u16 offset_value;
    void *spawn_sprite;
    void *hit_target;
    void *target;
    u16 render_flags;
    s32 trail_color;
    s32 state_index;
    s32 particle_index;
    s32 finish_tick;
    s32 particle_color;
    s32 effect_busy;
    s32 fade_out_tick;
    s32 target_tick;
    s32 blue_scaled;
    s32 green_scaled;
    s32 red_scaled;
    s32 owner_z;
    s32 effect_z;
    s32 tile_distance;

    owner = PTR(effect, 0);
    direction_steps = D_80024074;
    state_index = S16(effect, 0xA);
    object = (u8 *)owner - 0x20;
    object_data = PTR(object, 8);

    switch (state_index) {

    case 0:
        U32(sprite, 0xC) = 0x00808080;
        U16(sprite, 0x1E) = 0x1000;
        U16(sprite, 0x1C) = 0x1000;
        *(AggU12 *)((u8 *)effect + 0x98) = *(AggU12 *)&D_80026934;
        PTR(sprite, 8) = (u8 *)effect + 0x98;
        {
            u16 facing = U16(owner, 0x2A);
            D_8002694C[0] = 1;
            U16(effect, 0x7E) = (facing >> 9) & 7;
        }
        U16(effect, 0xA) += 1;

    case 1:
        origin_sprite = PTR(object, 0xC);
        if (func_8003DF74(PTR(origin_sprite, 8), origin_sprite, origin_offset, 0) == 0) {
            if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
                return;
            }
        }

        U16(motion, 2) = U16(object_data, 2);
        U16(motion, 6) = U16(object_data, 6);
        owner_z = U16(object_data, 0xA);
        U16(motion, 0xA) = owner_z;
        if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
            U16(motion, 2) = U16(motion, 2) + origin_offset[0];
            U16(motion, 6) = U16(motion, 6) + origin_offset[1];
            effect_z = U16(motion, 0xA) + origin_offset[2];
            U16(motion, 0xA) = effect_z;
            goto await_launch;
        }
        U16(motion, 0xA) = owner_z - 0x40;

await_launch:
        if (!(U16(PTR(effect, 4), 0) & 0x80)) {
            return;
        }

        if (!(U8(effect, 0x7A) & 4)) {
            effect_object = (u8 *)effect - 0x20;
            func_8004491C(effect_object, func_80045340);
            U16(sprite, 0x10) = 0x20;
            U8(sprite, 0xD) = 0x80;
            U8(sprite, 0xC) = 0x80;
            U8(sprite, 0xE) = 0x20;
            U16(sprite, 0x14) |= 0xC;
            U8(effect, 0x7A) |= 4;
        }

        hit_target = PTR(owner, 0x60);
        offset_value = 0x10;
        if (hit_target != 0) {
            object = PTR(hit_target, -0x18);
            U16(effect, 0x74) = U16(object, 2);
            U16(effect, 0x76) = U16(object, 6);
            {
                s32 height = D_800DDC40[U8(PTR(owner, 0x60), 0x13)] + 0x20;
                U16(effect, 0x78) = U16(object, 0xA) - height;
            }
            owner_sprite = PTR(owner, -0x14);
            U8(effect, 0xA4) = U8(owner_sprite, 0x24) + *(u8 *)&dirStepX[S16(effect, 0x7E)];
            U8(effect, 0xA5) = U8(owner_sprite, 0x25) + *(u8 *)&dirStepY[S16(effect, 0x7E)];
            {
                s32 grid;
                tile_distance = S8(owner, 0x72);
                grid = U8(owner_sprite, 0x24);
                if (tile_distance != grid) {
                    tile_distance -= grid;
                } else {
                    tile_distance = S8(owner, 0x73);
                    grid = U8(owner_sprite, 0x25);
                    tile_distance -= grid;
                }
            }
            if (tile_distance < 0) {
                tile_distance = -tile_distance;
            }
            U8(effect, 0x7B) = tile_distance * 2 - 1;
        } else {
            U8(effect, 0x7B) = (u32)offset_value;
            offset_value = (u16)direction_steps.p[S16(effect, 0x7E)].x << 4;
            {
                s16 travel_ticks;
                u16 y_step;
                U16(effect, 0x74) = U16(motion, 2) + (u32)offset_value;
                y_step = direction_steps.p[S16(effect, 0x7E)].y;
                travel_ticks = U8(effect, 0x7B);
                travel_ticks = (s8)travel_ticks;
                U16(effect, 0x76) = U16(motion, 6) + y_step * (s8)travel_ticks;
            }
            U16(effect, 0x78) = U16(owner, 0x88) - 0x50;
        }

        S32(motion, 0xC) = direction_steps.p[S16(effect, 0x7E)].x << 16;
        S32(motion, 0x10) = direction_steps.p[S16(effect, 0x7E)].y << 16;
        S32(motion, 0x14) = ((S16(effect, 0x78) << 16) - S32(motion, 8)) / S8(effect, 0x7B);
        U16(effect, 0x82) = 0;
        U16(effect, 0xA) += 1;
        return;

    case 2:
        trail_color = 0x60;
        do {
            object = func_8003FC64(0x12);
            object_data = (u8 *)object + 0x20;
            if (object != 0) {
                U16(object_data, 2) = 8;
                U16(object_data, 4) = 8;
                PTR(object, 0x10) = func_8002569C;
                func_8004491C(object, func_80045340);

                spawn_sprite = PTR(object, 0xC);

                U16(spawn_sprite, 0x10) = 0x20;
                U16(spawn_sprite, 0x14) |= 0xC;
                {
                    void *spawn_pos = PTR(object, 8);
                    U16(spawn_pos, 2) = U16(motion, 2);
                    U16(spawn_pos, 6) = U16(motion, 6);
                    U16(spawn_pos, 0xA) = U16(motion, 0xA);
                }
                spawn_sprite = PTR(object, 0xC);
                U16(spawn_sprite, 0x1E) = 0x1000;
                U16(spawn_sprite, 0x1C) = 0x1000;
                U8(spawn_sprite, 0xD) = trail_color;
                U8(spawn_sprite, 0xC) = trail_color;
                U8(spawn_sprite, 0xE) = 0x10;
                U8(object_data, 0x38) = 0x10;
                U8(object_data, 0x37) = trail_color;
                U8(object_data, 0x36) = trail_color;
                *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&D_80026934;
                PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
            }

            if ((s16)func_800A4778(U16(motion, 2), U16(motion, 6), S16(motion, 0xA),
                                   PTR(owner, 0x60)) != 0) {
                goto collision_hit;
            }

            U8(effect, 0x7B) = U8(effect, 0x7B) - 1;
            if (S8(effect, 0x7B) <= 0) {
                if (PTR(owner, 0x60) != 0) {
                    goto reach_target;
                }
                U16(effect, 0xA) = 7;
                U16(effect, 0x82) = 0;
                render_flags = U16(sprite, 0x14);
                U8(sprite, 0xE) = 0;
                U8(sprite, 0xD) = 0;
                U8(sprite, 0xC) = 0;
                goto set_render_flag;
            }

            S32(motion, 0xC) = ((S16(effect, 0x74) << 16) - S32(motion, 0)) / S8(effect, 0x7B);
            S32(motion, 0x10) = ((S16(effect, 0x76) << 16) - S32(motion, 4)) / S8(effect, 0x7B);
            S32(motion, 0x14) = ((S16(effect, 0x78) << 16) - S32(motion, 8)) / S8(effect, 0x7B);
            S32(motion, 0) += S32(motion, 0xC);
            S32(motion, 4) += S32(motion, 0x10);
            S32(motion, 8) += S32(motion, 0x14);
        } while (1);

    case 3:
        if (S16(effect, 0x96) == 0) {
            U16(effect, 0x96) = 1;
            U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
        } else {
            U16(effect, 0x96) = 0;
            U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
        }

        object = func_8003FC64(0x12);
        object_data = (u8 *)object + 0x20;
        if (object != 0) {
            U16(object_data, 2) = 8;
            U16(object_data, 4) = 8;
            U16(object_data, 0xA) = 0x30;
            S16(object_data, 0xC) = -0xDE;
            PTR(object, 0x10) = func_800257E0;
            spawn_sprite = PTR(object, 0xC);
            U16(spawn_sprite, 0x10) = 0x20;
            U16(spawn_sprite, 0x14) |= 0xC;
            {
                void *spawn_pos = PTR(object, 8);
                U16(spawn_pos, 2) = U16(motion, 2);
                U16(spawn_pos, 6) = U16(motion, 6);
                U16(spawn_pos, 0xA) = U16(motion, 0xA);
            }
            *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&D_80026940;
            PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
        }
        U8(effect, 0x92) = 0;
        U8(effect, 0x91) = 0;
        U8(effect, 0x90) = 0;
        U16(effect, 0xA) = 4;
        U16(effect, 0x82) = 0;
        return;

    case 4:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        fade_out_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
        if (fade_out_tick >= 0x14) {
            goto finish_fade;
        }

        U8(sprite, 0xC) = ((0x14 - fade_out_tick) * 0xE0) / 0x14;
        U8(sprite, 0xD) = ((0x14 - S16(effect, 0x82)) * 0xE0) / 0x14;
        U8(sprite, 0xE) = ((0x14 - S16(effect, 0x82)) * 0x20) / 0x14;
        if (S16(effect, 0x96) == 0) {
            U16(effect, 0x96) = 1;
            U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
        } else {
            U16(effect, 0x96) = 0;
            U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
        }

        particle_index = 0;
loop_0:
        {
            particle_color = func_80069EF8();
            {
                s32 base_color;
                s32 brightness;
                target = (u8 *)effect - 0x20;
                base_color = 0x0020E0E0;
                particle_color &= 0xFF;
                brightness = particle_color | 0x80;
                func_800250B0(target, S16(effect, 0x7E), base_color, brightness, 0, 0, 0);
            }
            particle_index += 1;
        }
        if (particle_index < 4)
            goto loop_0;
        return;

finish_fade:
        U16(effect, 0x82) = 0;
        U16(effect, 0xA) += 1;
        return;

    case 5:
        U16(effect, 0x82) = U16(effect, 0x82) + 1;
        blue_scaled = S16(effect, 0x82) * 0x20;
        U8(effect, 0x92) = blue_scaled / 0x28;
        green_scaled = S16(effect, 0x82) * 8;
        green_scaled = (green_scaled - S16(effect, 0x82)) * 32;
        U8(effect, 0x91) = green_scaled / 0x28;
        red_scaled = S16(effect, 0x82) * 8;
        red_scaled = (red_scaled - S16(effect, 0x82)) * 32;
        U8(effect, 0x90) = red_scaled / 0x28;

        object = PTR(PTR(owner, 0x60), -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
            func_800251E8((D_800DDC40[U8(PTR(owner, 0x60), 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (D_800DDC40[U8(PTR(owner, 0x60), 0x13)] >> 1)));
        }
        if (S16(effect, 0x82) >= 0x28) {
            U16(effect, 0x82) = 0;
            U16(effect, 0xA) += 1;
            return;
        }
        return;

    case 6:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        target_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
        if (target_tick >= 0x24) {
            U8(effect, 0x92) = ((0x46 - target_tick) * 0x20) / 0x23;
            U8(effect, 0x91) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
            U8(effect, 0x90) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
        }

        object = PTR(PTR(owner, 0x60), -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
            func_800251E8((D_800DDC40[U8(PTR(owner, 0x60), 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (D_800DDC40[U8(PTR(owner, 0x60), 0x13)] >> 1)));
        }

        target = PTR(owner, 0x60);
        U32(target, 0x1C) |= 0x10000000;
        target_data = PTR(target, -0x14);
        if (S16(effect, 0x82) >= 0x24) {
            U8(target_data, 0xC) -= 3;
            U8(target_data, 0xD) -= 3;
            U8(target_data, 0xE) += 2;
        } else {
            U8(target_data, 0xC) += 3;
            U8(target_data, 0xD) += 3;
            U8(target_data, 0xE) -= 2;
        }
        if (S16(effect, 0x82) < 0x46) {
            return;
        }

        {
            void *released = PTR(owner, 0x60);
            target_data = PTR(released, -0x14);
            U32(released, 0x1C) &= 0xEFFFFFFF;
        }
        U8(target_data, 0xE) = 0x80;
        U8(target_data, 0xD) = 0x80;
        U8(target_data, 0xC) = 0x80;
        func_800240B8(PTR(owner, 0x60), U8(effect, 9), owner);
        U16(effect, 0x82) = 0x14;
        U16(effect, 0xA) += 1;
        return;

    case 7:
        finish_tick = U16(effect, 0x82);
        U16(effect, 0x82) = finish_tick + 1;
        if ((s16)finish_tick < 0x15) {
            return;
        }
        effect_busy = D_8002694C[0];
        U16(effect, 0x82) = finish_tick;
        if (effect_busy == 0) {
            S32(D_8007CCD8 + 13096, 0x346C) = 0;
            U16(effect, -2) |= 0x8000;
            U32((void *)D_80080000, 0x14A0) |= 0x8000;
            return;
        }
        goto clear_busy;
    default:
        return;
    }
collision_hit:
    U16(effect, 0xA) = 7;
    U16(effect, 0x82) = 0;
    render_flags = U16(sprite, 0x14);
set_render_flag:
    render_flags |= 0x80;
    U16(sprite, 0x14) = render_flags;
    return;

reach_target:
    U16(effect, 0xA) = 3;
    U16(effect, 0x82) = 0;
    object = PTR(PTR(owner, 0x60), -0x18);
    U16(motion, 2) = U16(object, 2);
    U16(motion, 6) = U16(object, 6);
    U16(motion, 0xA) = U16(effect, 0x78);
    func_800A56E0(0x300);
    return;

clear_busy:
    D_8002694C[0] = 0;

    return;
}
