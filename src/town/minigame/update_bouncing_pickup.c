#include "common.h"
#include "town/minigame.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/town_state.h"

typedef struct S_800206D0_0 {
    s16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    void * unk_04;
    u8 pad_08[0x15];
    u8 unk_1D;
    u8 pad_1E[0x36];
    s16 unk_54;
    s16 unk_56;
} S_800206D0_0;   /* arg0 in update_bouncing_pickup */

typedef struct S_800206D0_1 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u16 unk_20;
} S_800206D0_1;   /* object in update_bouncing_pickup */

extern void advance_sprite_animation_and_textures(void *);
extern void SD_Call(s32);
extern s32 rand(void);
extern void unlink_scene_list_node(void *);
extern s32 handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(void *, void *, void *, void *);

extern s32 town_money[];
extern TownRewardValues D_80020020;
extern u8 minigame_source_bounds[];
extern s32 minigame_pickup_sprite_sources[];
extern s32 pickup_reward_total[];
extern s32 D_8007947C[];
extern u8 D_800D0420[];

/* Updates a bouncing pickup, awards its value on collection, and expires it. */
void update_bouncing_pickup(void *pickup, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_800206D0_1 *source_object = ((S_800206D0_0 *)pickup)->unk_04;
    TownRewardValues reward_units = D_80020020;
    s32 timer;
    s32 reward = 1;
    u32 state;

    if (source_object->unk_20 & 8) {
        ((S_800206D0_0 *)pickup)->unk_00 = 6;
    }

    state = (u32)((S_800206D0_0 *)pickup)->unk_00;
    switch (state) {

    case 0:
    {
        s32 denomination;
        s32 scaled_count;

        denomination = ((S_800206D0_0 *)pickup)->unk_54;
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
        scaled_count = source_object->unk_1E / reward;
        reward = scaled_count % 10;
        if (((S_800206D0_0 *)pickup)->unk_56 < reward) {
            sprite->flags &= 0xFF7F;
        } else {
            sprite->flags |= 0x80;
        }
        ((S_800206D0_0 *)pickup)->unk_1D = 0;
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
        denomination = ((S_800206D0_0 *)pickup)->unk_54;
        if (denomination == 0) {
            sprite->clut += 5;
        } else if (denomination == 1) {
            sprite->clut -= 5;
        }
        ((S_800206D0_0 *)pickup)->unk_1D = 0;
        ((S_800206D0_0 *)pickup)->unk_00 = 2;
    }

    case 2:
        advance_sprite_animation_and_textures(sprite);
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        motion->velocity_z += 0x30000;
        timer = --((S_800206D0_0 *)pickup)->unk_02.s;
        if ((s16)timer > 0) {
            return;
        }
        SD_Call(0x501);
        motion->z.v = 0xFFC00000;
        motion->velocity_z = ((rand() & 0xFF) << 11) + 0xFFE80000;
        ((S_800206D0_0 *)pickup)->unk_02.u = (rand() & 0xF) + 30;
        ((S_800206D0_0 *)pickup)->unk_00 = 3;
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
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(minigame_source_bounds, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            ((S_800206D0_0 *)pickup)->unk_00 = 6;
        }
        timer = --((S_800206D0_0 *)pickup)->unk_02.s;
        if ((s16)timer > 0) {
            return;
        }
        ((S_800206D0_0 *)pickup)->unk_02.u = 180;
        ((S_800206D0_0 *)pickup)->unk_00 = 4;
        idle_frame = minigame_pickup_sprite_sources[((S_800206D0_0 *)pickup)->unk_54];
        sprite->clut = 0;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->source = idle_frame;
        motion->z.v = floor_z;
        return;
    }

    case 4:
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(minigame_source_bounds, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            ((S_800206D0_0 *)pickup)->unk_00 = 6;
        }
        timer = --((S_800206D0_0 *)pickup)->unk_02.s;
        if ((s16)timer > 0) {
            return;
        }
        ((S_800206D0_0 *)pickup)->unk_02.u = 31;
        ((S_800206D0_0 *)pickup)->unk_00 = 5;
        return;

    case 5:
        if ((((S_800206D0_0 *)pickup)->unk_02.s >> 2) & 1) {
            sprite->flags |= 0x80;
        } else {
            sprite->flags &= 0xFF7F;
        }
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(minigame_source_bounds, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) != 0) {
            SD_Call(0x516);
            reward = ((s32 *)&reward_units)[((S_800206D0_0 *)pickup)->unk_54] * 100;
            town_money[0] += reward;
            pickup_reward_total[0] += reward;
            ((S_800206D0_0 *)pickup)->unk_00 = 6;
        }
        timer = --((S_800206D0_0 *)pickup)->unk_02.s;
        if ((s16)timer > 0) {
            return;
        }
        ((S_800206D0_0 *)pickup)->unk_00 = 6;
        return;

    case 6:
        unlink_scene_list_node((u8 *)pickup + 8);
        (*(u16 *)((u8 *)pickup + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    }
}
