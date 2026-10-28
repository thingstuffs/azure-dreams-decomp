#include "common.h"
#include "town/scene/active_object_overlap_g00529.h"
#include "town/minigame.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/town_state.h"

typedef struct S_800236BC_1 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x15];
    u8 unk_1D;
    u8 pad_1E[0x36];
    s16 unk_54;
} S_800236BC_1;   /* arg0 in update_bouncing_pickup_after_hit */

typedef struct S_800236BC_3 {
    u8 pad_00[0x62];
    u16 unk_62;
} S_800236BC_3;   /* ((S_800236BC_1 *)arg0)->unk_00 in update_bouncing_pickup_after_hit */

extern void advance_sprite_animation_and_textures(void *);
extern void SD_Call(s32);
extern s32 rand(void);
extern void unlink_scene_list_node(void *);

extern s32 town_money[];
extern TownRewardValues D_80020278;
extern Box minigame_pickup_bounds[];
extern s32 D_800244DC[];
extern s32 pickup_reward_total[];
extern Box D_800D0420;

/* Updates a bouncing pickup, awards its value on collision, and expires it. */
void update_bouncing_pickup_after_hit(void *object, ObjectPosition *motion, SpriteFrameState *sprite)
{
    union { TownRewardValues values; s32 table[3]; } reward_values;
    s16 state;
    s32 sprite_data;
    s32 reward_amount;
    s32 reward_units;
    s32 *reward_table = reward_values.table;
    u32 collision_addr;

    reward_values.values = D_80020278;

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    ((S_800236BC_3 *)(((S_800236BC_1 *)object)->unk_00))->unk_62 |= 2;

    state = ((S_800236BC_1 *)object)->unk_04.s;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(sprite);
        motion->velocity_z += 0x40000;
        ((S_800236BC_1 *)object)->unk_1D = 0;
        if (motion->z.v < 0) {
            return;
        }
        SD_Call(0x501);
        motion->z.v = 0;
        ((S_800236BC_1 *)object)->unk_06.s = 15;
        motion->velocity_x = ((rand() % 320) - 64) << 12;
        motion->velocity_y = (rand() % 96 + 128) << 12;
        motion->velocity_z = 0xFFF00000;
        ((S_800236BC_1 *)object)->unk_04.u++;
        return;

    case 1:
        advance_sprite_animation_and_textures(sprite);
        motion->velocity_z += 0x40000;
        ((S_800236BC_1 *)object)->unk_06.u--;
        if (motion->z.v < 0) {
            return;
        }
        SD_Call(0x501);
        if (((S_800236BC_1 *)object)->unk_06.s > 0) {
            motion->z.v = 0;
            motion->velocity_z = -motion->velocity_z;
            return;
        }
        motion->z.v = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->velocity_z = ((rand() & 0xFF) << 11) - 0x150000;
        ((S_800236BC_1 *)object)->unk_06.s = (rand() & 0xF) + 30;
        ((S_800236BC_1 *)object)->unk_04.u++;
        return;

    case 2:
        advance_sprite_animation_and_textures(sprite);
        motion->velocity_z += 0x30000;
        ((S_800236BC_1 *)object)->unk_06.u--;
        collision_addr = 0x80020000;
        if (motion->z.v >= 0) {
            motion->z.v = 0;
            if (((S_800236BC_1 *)object)->unk_06.s < 0) {
                sprite_data = D_800244DC[((S_800236BC_1 *)object)->unk_54];
                sprite->clut = 0;
                sprite->unk_04 = 0;
                sprite->frame_ticks = 0;
                sprite->source = sprite_data;
                motion->velocity_z = 0;
                ((S_800236BC_1 *)object)->unk_06.s = 150;
                ((S_800236BC_1 *)object)->unk_04.u++;
            } else {
                motion->velocity_z = -motion->velocity_z >> 1;
            }
        }
        collision_addr = (u32)&minigame_pickup_bounds;
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes((void *)collision_addr, motion, &D_800D0420, &view_reference_entity) == 0) {
            return;
        }
        SD_Call(0x516);
        {
            reward_units = reward_values.table[((S_800236BC_1 *)object)->unk_54];

            {
                s32 reward_total, collected_total;
                reward_amount = reward_units * 100;
                reward_total = town_money[0];
                collected_total = pickup_reward_total[0];
                town_money[0] = reward_total + reward_amount;
                pickup_reward_total[0] = collected_total + reward_amount;
            }
            ((S_800236BC_1 *)object)->unk_04.s = 255;
            return;

        }

    case 3:
        ((S_800236BC_1 *)object)->unk_06.u--;
        if (((S_800236BC_1 *)object)->unk_06.s < 0) {
            ((S_800236BC_1 *)object)->unk_06.s = 31;
            ((S_800236BC_1 *)object)->unk_04.u++;
        }
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(minigame_pickup_bounds, motion, &D_800D0420, &view_reference_entity) == 0) {
            return;
        }
        SD_Call(0x516);
        reward_units = reward_table[((S_800236BC_1 *)object)->unk_54];
        {
            s32 reward_total, collected_total;
            reward_amount = reward_units * 100;
            reward_total = town_money[0];
            collected_total = pickup_reward_total[0];
            town_money[0] = reward_total + reward_amount;
            pickup_reward_total[0] = collected_total + reward_amount;
        }
        ((S_800236BC_1 *)object)->unk_04.s = 255;
        return;

    case 4:
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(minigame_pickup_bounds, motion, &D_800D0420, &view_reference_entity) != 0) {
            SD_Call(0x516);
            reward_amount = reward_table[((S_800236BC_1 *)object)->unk_54] * 100;
            town_money[0] += reward_amount;
            pickup_reward_total[0] += reward_amount;
            ((S_800236BC_1 *)object)->unk_04.s = 255;
        }
        {
            s32 sprite_flags;
            if ((((S_800236BC_1 *)object)->unk_06.u >> 2) & 1) {
                sprite_flags = sprite->flags | 0x80;
            } else {
                sprite_flags = sprite->flags & 0xFF7F;
            }
            sprite->flags = sprite_flags;
        }
        ((S_800236BC_1 *)object)->unk_06.u--;
        if (((S_800236BC_1 *)object)->unk_06.s > 0) {
            return;
        }
        ((S_800236BC_1 *)object)->unk_04.s = 255;
        return;

    case 255:
        unlink_scene_list_node((u8 *)object + 8);
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
