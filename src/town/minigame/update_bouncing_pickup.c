#include "common.h"
#include "town/scene/active_object_overlap_g00529.h"
#include "town/minigame.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/town_state.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/scene/object.h"
#include "town/minigame/pickup_data.h"
#include "town/minigame/source_bounds_data.h"
#include "town/data.h"



extern s32 town_money[];
extern TownRewardValues D_80020020;
extern s32 D_8007947C[];
extern Box D_800D0420;

/* Updates a bouncing pickup, awards its value on collection, and expires it. */
void update_bouncing_pickup(minigame_pickup_source *pickup, ObjectPosition *motion, SpriteFrameState *sprite)
{
    TownEffect *source_object = pickup->owner;
    TownRewardValues reward_units = D_80020020;
    s32 timer;
    s32 reward = 1;
    u32 state;

    if (source_object->flags & 8) {
        pickup->kind = 6;
    }

    state = (u32)pickup->kind;
    switch (state) {

    case 0:
    {
        s32 denomination;
        s32 scaled_count;

        denomination = pickup->x;
        switch (denomination) {
        case 1:
            reward = 10;
            break;
        case 2:
            reward = 100;
            break;
        default:
            break;
        }
        scaled_count = source_object->ticks / reward;
        reward = scaled_count % 10;
        if (pickup->y < reward) {
            sprite->flags &= 0xFF7F;
        } else {
            sprite->flags |= 0x80;
        }
        pickup->unk_1D = 0;
        return;
    }

    case 1:
    {
        s32 denomination;

        sprite->unk_00 = D_8007947C;
        sprite->source = D_8007947C[1];
        sprite->unk_04 = 0;
        sprite->frame_ticks = rand() & 3;
        sprite->flags &= 0xFF7F;
        denomination = pickup->x;
        if (denomination == 0) {
            sprite->clut += 5;
        } else if (denomination == 1) {
            sprite->clut -= 5;
        }
        pickup->unk_1D = 0;
        pickup->kind = 2;
    }

    case 2:
        advance_sprite_animation_and_textures(sprite);
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        motion->velocity_z += 0x30000;
        timer = --pickup->timer;
        if ((s16)timer > 0) {
            return;
        }
        SD_Call(0x501);
        motion->z.v = 0xFFC00000;
        motion->velocity_z = ((rand() & 0xFF) << 11) + 0xFFE80000;
        pickup->timer = (rand() & 0xF) + 30;
        pickup->kind = 3;
        return;

    case 3:
    {
        s32 floor_z = 0xFFC00000;
        s32 idle_frame;

        advance_sprite_animation_and_textures(sprite);
        motion->z.v += motion->velocity_z;
        motion->velocity_z += 0x30000;
        if (floor_z < motion->z.v) {
            SD_Call(0x501);
            motion->z.v = floor_z;
            motion->velocity_z = -motion->velocity_z >> 1;
        }
        if (offset_boxes_overlap(minigame_source_bounds, motion, &D_800D0420, &view_reference_entity) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[pickup->x] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            pickup->kind = 6;
        }
        timer = --pickup->timer;
        if ((s16)timer > 0) {
            return;
        }
        pickup->timer = 180;
        pickup->kind = 4;
        idle_frame = minigame_pickup_sprite_sources[pickup->x];
        sprite->clut = 0;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->source = idle_frame;
        motion->z.v = floor_z;
        return;
    }

    case 4:
        if (offset_boxes_overlap(minigame_source_bounds, motion, &D_800D0420, &view_reference_entity) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[pickup->x] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            pickup->kind = 6;
        }
        timer = --pickup->timer;
        if ((s16)timer > 0) {
            return;
        }
        pickup->timer = 31;
        pickup->kind = 5;
        return;

    case 5:
        if ((pickup->timer >> 2) & 1) {
            sprite->flags |= 0x80;
        } else {
            sprite->flags &= 0xFF7F;
        }
        if (offset_boxes_overlap(minigame_source_bounds, motion, &D_800D0420, &view_reference_entity) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[pickup->x] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            pickup->kind = 6;
        }
        timer = --pickup->timer;
        if ((s16)timer > 0) {
            return;
        }
        pickup->kind = 6;
        return;

    case 6:
        unlink_scene_list_node((u8 *)pickup + 8);
        (((ObjectNodeHeader *)pickup - 1)->flags) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    }
}
