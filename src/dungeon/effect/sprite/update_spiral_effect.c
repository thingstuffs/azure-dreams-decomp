#include "common.h"
#include "dungeon/effect/sprite.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "slus.h"


/* Update a spiraling effect's motion and color, then retire it below its height limit. */
void update_spiral_effect(RadialEffectBody *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
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

    state = effect->unk_4C;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(sprite);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
        }

        motion->x.w.i = (s16)(effect->unk_0C +
            ((rsin((s16)effect->unk_18) *
              effect->unk_1C.at02.v) >> 12));
        motion->y.w.i = (s16)(effect->unk_0E +
            ((rcos((s16)effect->unk_18) *
              effect->unk_1C.at02.v) >> 12));

        motion->velocity_z += 0xFFFE0000 +
            ((rand() & 0xFF) << 9);
        effect->unk_18 = (s16)(effect->unk_18 + 0x80 +
            (rand() & 0x3F));

        effect->unk_28 += effect->unk_34;
        radius_step = effect->unk_28;
        radius = effect->unk_1C.at00.v;
        if (radius <= 0) {
            radius_step >>= 2;
            effect->unk_1C.at00.v = radius_step + radius;
        } else {
            effect->unk_1C.at00.v = radius + radius_step;
        }

        red = sprite->color.c.r;
        green = sprite->color.c.g;
        sprite->color.c.r = red - (red >> 4);
        sprite->color.c.g = green - (green >> 4);
        blue = sprite->color.c.b;
        sprite->color.c.b = blue - (blue >> 4);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
        }

        if (motion->z.w.i < effect->unk_10 - 0x60) {
            effect->unk_4C++;
        }
        break;
    case 1:
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        (*(u16 *)((u8 *)effect + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
