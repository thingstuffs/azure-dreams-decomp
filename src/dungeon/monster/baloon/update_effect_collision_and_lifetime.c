#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80D65534_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_80D65534_0;   /* arg1 in update_effect_collision_and_lifetime */

typedef struct S_80D65534_1_pre {
    u16 unk_00;
} S_80D65534_1_pre;   /* the 0x2 bytes before arg0 in update_effect_collision_and_lifetime, addressed as arg0[-1] */

typedef struct S_80D65534_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x8];
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    s16 unk_0E;
    u8 pad_10[0x8];
    u16 unk_18;
    u8 pad_1A[0x12];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} S_80D65534_1;   /* arg0 in update_effect_collision_and_lifetime */

extern void advance_sprite_animation_and_textures(void *entity);
extern s32 check_left_tile_and_center_height(u16 x, u16 y, s16 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Updates effect motion, terrain collisions, visual properties, and lifetime. */
void update_effect_collision_and_lifetime(void *effect, S_80D65534_0 *position, SpriteFrameState *visual)
{
    s16 life_left;
    s32 current_z;
    s32 life_scale;
    s32 terrain_z;
    u16 updated_value;
    u16 x;
    u16 z;

    position->unk_08.at00.v += ((S_80D65534_1 *)effect)->unk_34;
    ((S_80D65534_1 *)effect)->unk_34 += ((S_80D65534_1 *)effect)->unk_40;

    x = position->unk_00.at02.v;
    z = position->unk_08.at02.v;
    current_z = position->unk_08.at02u.v;
    terrain_z = sample_terrain_surface_height(x,
                              position->unk_04.at02.v,
                              (s16)(z - 4));
    if (terrain_z - 0x10 < current_z) {
        ((S_80D65534_1 *)effect)->unk_34 = 0;
        position->unk_08.at02u.v =
            sample_terrain_surface_height(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          (s16)(position->unk_08.at02.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
        if (((S_80D65534_1 *)effect)->unk_02 == 0) {
            ((S_80D65534_1 *)effect)->unk_02 = 1;
        }
    }

    if (((S_80D65534_1 *)effect)->unk_02 == 1) {
        position->unk_00.at00.v += ((S_80D65534_1 *)effect)->unk_2C;
        ((S_80D65534_1 *)effect)->unk_2C += ((S_80D65534_1 *)effect)->unk_38;
        if (sample_terrain_surface_height(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          position->unk_08.at02u.v) < 0x200 &&
            (s16)check_left_tile_and_center_height(position->unk_00.at02.v,
                               position->unk_04.at02.v,
                               position->unk_08.at02u.v) != 0) {
            position->unk_00.at00.v -= ((S_80D65534_1 *)effect)->unk_2C;
            ((S_80D65534_1 *)effect)->unk_2C = 0;
            ((S_80D65534_1 *)effect)->unk_38 = 0;
        }

        position->unk_04.at00.v += ((S_80D65534_1 *)effect)->unk_30;
        ((S_80D65534_1 *)effect)->unk_30 += ((S_80D65534_1 *)effect)->unk_3C;
        if (sample_terrain_surface_height(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          position->unk_08.at02u.v) < 0x200 &&
            (s16)check_left_tile_and_center_height(position->unk_00.at02.v,
                               position->unk_04.at02.v,
                               position->unk_08.at02u.v) != 0) {
            position->unk_04.at00.v -= ((S_80D65534_1 *)effect)->unk_30;
            ((S_80D65534_1 *)effect)->unk_30 = 0;
            ((S_80D65534_1 *)effect)->unk_3C = 0;
        }
    }

    life_scale = (((S_80D65534_1 *)effect)->unk_0C.s << 7) /
            ((S_80D65534_1 *)effect)->unk_0E;
    visual->color.c.b = life_scale;
    visual->color.c.g = life_scale;
    visual->color.c.r = life_scale;

    updated_value = ((S_80D65534_1 *)effect)->unk_18 + 1;
    ((S_80D65534_1 *)effect)->unk_18 = updated_value;
    if ((s16)updated_value == 3) {
        advance_sprite_animation_and_textures(visual);
        ((S_80D65534_1 *)effect)->unk_18 = 0;
    }

    updated_value = visual->scale_x + 0xC8;
    visual->scale_x = updated_value;
    if (updated_value > 0x1000) {
        visual->scale_x = 0x1000;
    }

    updated_value = visual->scale_y + 0xC8;
    visual->scale_y = updated_value;
    if (updated_value > 0x1000) {
        visual->scale_y = 0x1000;
    }

    life_left = ((S_80D65534_1 *)effect)->unk_0C.u - 1;
    ((S_80D65534_1 *)effect)->unk_0C.u = life_left;
    if ((life_left << 16) <= 0) {
        ((S_80D65534_1_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
