#include "common.h"
#include "dungeon/effect/sprite.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

extern void advance_sprite_animation_and_textures(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);


typedef struct S_800D7D30_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x6];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x8];
    s32 unk_34;
    u8 pad_38[0x14];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800D7D30_1;   /* arg0 in update_spiral_effect */

/* Update a spiraling effect's motion and color, then retire it below its height limit. */
void update_spiral_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    s32 radius_step;
    s32 velocity_y;
    s32 velocity_z;
    s32 radius;
    u32 red;
    u32 green;
    u32 blue;
    s16 state;

    velocity_y = motion->velocity_y;
    velocity_z = motion->velocity_z;
    motion->x.v += motion->velocity_x;
    motion->y.v += velocity_y;
    motion->z.v += velocity_z;

    state = ((S_800D7D30_1 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(sprite);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
        }

        motion->x.w.i = (s16)(((S_800D7D30_1 *)effect)->unk_0C +
            ((func_800644B8(((S_800D7D30_1 *)effect)->unk_18.s) *
              ((S_800D7D30_1 *)effect)->unk_1C.at02.v) >> 12));
        motion->y.w.i = (s16)(((S_800D7D30_1 *)effect)->unk_0E +
            ((func_80064584(((S_800D7D30_1 *)effect)->unk_18.s) *
              ((S_800D7D30_1 *)effect)->unk_1C.at02.v) >> 12));

        motion->velocity_z += 0xFFFE0000 +
            ((rand() & 0xFF) << 9);
        ((S_800D7D30_1 *)effect)->unk_18.s = (s16)(((S_800D7D30_1 *)effect)->unk_18.u + 0x80 +
            (rand() & 0x3F));

        ((S_800D7D30_1 *)effect)->unk_28 += ((S_800D7D30_1 *)effect)->unk_34;
        radius_step = ((S_800D7D30_1 *)effect)->unk_28;
        radius = ((S_800D7D30_1 *)effect)->unk_1C.at00.v;
        if (radius <= 0) {
            radius_step >>= 2;
            ((S_800D7D30_1 *)effect)->unk_1C.at00.v = radius_step + radius;
        } else {
            ((S_800D7D30_1 *)effect)->unk_1C.at00.v = radius + radius_step;
        }

        red = sprite->color.c.r;
        green = sprite->color.c.g;
        sprite->color.c.r = red - (red >> 4);
        sprite->color.c.g = green - (green >> 4);
        blue = sprite->color.c.b;
        sprite->color.c.b = blue - (blue >> 4);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
        }

        if (motion->z.w.i < ((S_800D7D30_1 *)effect)->unk_10 - 0x60) {
            ((S_800D7D30_1 *)effect)->unk_4C.u++;
        }
        break;
    case 1:
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        (*(u16 *)((u8 *)effect + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
