#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/particle.h"


extern s16 encounter_blink_update_flag;
extern s16 sample_terrain_surface_height(u16, u16, s16);


typedef struct S_80165AB8_0 {
    u8 pad_00[0x17];
    u8 phase; /* 0x17 */
    u8 pad_18[0x1A];
    union { s16 s; u16 u; } ticks; /* 0x32 */   /* accessed as both */
    u8 pad_34[0x20];
    s32 unk_54;
    u8 pad_58[0x8];
    s32 gravity; /* 0x60 */
} S_80165AB8_0;   /* arg0 in update_landing_particle_fade */

typedef struct S_80165AB8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } x; /* 0x00 */   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } y; /* 0x04 */   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } z; /* 0x08 */   /* overlapping accesses */
    s32 velocity_x; /* 0x0C */
    s32 velocity_y; /* 0x10 */
    s32 velocity_z; /* 0x14 */
} S_80165AB8_1;   /* arg1 in update_landing_particle_fade */

typedef struct S_80165AB8_2 {
    u8 pad_00[0xC];
    s8 red; /* 0x0C */
    s8 green; /* 0x0D */
    s8 blue; /* 0x0E */
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 scale_x; /* 0x1C */
    u16 scale_y; /* 0x1E */
} S_80165AB8_2;   /* arg2 in update_landing_particle_fade */

/* Updates object motion, landing, and fading before marking it finished. */
void update_landing_particle_fade(u8 *object_arg, u8 *motion_arg, u8 *sprite_arg)
{
    S_80165AB8_2 *sprite = sprite_arg;
    S_80165AB8_1 *motion = motion_arg;
    S_80165AB8_0 *object = object_arg;
    s32 height;
    u32 state;
    s32 counter_check;
    s32 next_tick;

    state = object->phase;
    switch (state) {
    case 0:
        motion->x.at00.v += motion->velocity_x;
        motion->y.at00.v += motion->velocity_y;
        motion->z.at00.v += motion->velocity_z;

        height = motion->z.at02.v;
        motion->velocity_z += object->gravity;
        if ((sample_terrain_surface_height(motion->x.at02.v,
                           motion->y.at02.v,
                           (s16)(motion->z.at02u.v - 4)) - 15) < height) {
            object->unk_54 = 0;
            motion->z.at02.v =
                sample_terrain_surface_height(motion->x.at02.v,
                              motion->y.at02.v,
                              (s16)(motion->z.at02u.v - 4)) - 2;
            motion->z.at00u.v = 0;
            object->ticks.s = 0;
            object->phase++;
        }
        counter_check = object->ticks.u;
        next_tick = counter_check + 1;
        counter_check = (s16)counter_check < 60;
        object->ticks.u = next_tick;
        if (counter_check) {
            return;
        }

        (*(u16 *)((u8 *)object + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;

    case 1:
    {
        s32 source_size = sprite->scale_y;
        next_tick = source_size << 1;
        next_tick += source_size;
        sprite->scale_y = next_tick;
        sprite->scale_x = next_tick;
        object->ticks.s = 0;
        object->phase++;
        return;
    }

    case 2:
        if (encounter_blink_update_flag == 0) {
            return;
        }
        object->ticks.s = 0;
        object->phase++;
        return;

    case 3:
        if ((s16)object->ticks.u++ < 20) {
            return;
        }
        sprite->unk_10 = 0;
        sprite->unk_14 |= 0xC;

        object->ticks.s = 0;
        object->phase++;
        return;

    case 4:
        sprite->red =
            ((10 - object->ticks.s) * 255) / 10;
        sprite->green = sprite->blue =
            ((10 - object->ticks.s) * 32) / 10;
        counter_check = object->ticks.u;
        next_tick = counter_check + 1;
        counter_check = (s16)counter_check < 10;
        object->ticks.u = next_tick;
        if (counter_check) {
            return;
        }

        (*(u16 *)((u8 *)object + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    default:
        return;
    }
}
