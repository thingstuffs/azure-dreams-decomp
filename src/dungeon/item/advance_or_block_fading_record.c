#include "common.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/item.h"
#include "slus.h"



/* Flag blocked records or advance their state, damping motion and fading color when enabled. */
void advance_or_block_fading_record(RadialParticleBurstBody *state, ObjectPosition *motion, SpriteFrameState *record)
{
    u16 update_count;
    u8 red;
    u8 blue;
    u8 green;

    if (record->flags & 0xE000) {
        NODE_HEADER(state)->flags =
            (s16)(NODE_HEADER(state)->flags | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    update_count = state->tick_count.u + 1;
    state->tick_count.u = update_count;
    if ((update_count << 0x10) > 0) {
        record->flags =
            (u16)(record->flags & 0xFF7F);
        advance_sprite_animation_and_textures(record);
    }
    if (state->radial_mode != 0) {
        motion->x.v =
            (s32)(motion->x.v + motion->velocity_x);
        motion->y.v =
            (s32)(motion->y.v + motion->velocity_y);
        motion->z.v =
            (s32)(motion->z.v + motion->velocity_z);
        motion->velocity_x =
            (s32)(motion->velocity_x - (motion->velocity_x >> 2));
        motion->velocity_y =
            (s32)(motion->velocity_y - (motion->velocity_y >> 2));
        motion->velocity_z =
            (s32)(motion->velocity_z - (motion->velocity_z >> 2));
        red = record->color.c.r;
        green = record->color.c.g;
        record->color.c.r =
            (u8)(red - (red >> 1));
        blue = record->color.c.b;
        record->color.c.g =
            (u8)(green - (green >> 1));
        record->color.c.b =
            (u8)(blue - (blue >> 1));
    }
}
