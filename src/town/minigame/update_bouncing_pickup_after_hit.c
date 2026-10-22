#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800206D0_arg1.h"
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
extern s32 handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(void *, void *, void *, void *);

extern s32 town_money[];
extern TownRewardValues D_80020278;
extern u8 D_80024488[];
extern s32 D_800244DC[];
extern s32 pickup_reward_total[];
extern u8 D_800D0420[];

/* Updates a bouncing pickup, awards its value on collision, and expires it. */
void update_bouncing_pickup_after_hit(void *object, void *motion, void *sprite)
{
    TownRewardValues reward_values = D_80020278;
    s16 state;
    s32 sprite_data;
    s32 reward_amount;
    s32 reward_units;
    s32 *reward_table = (s32 *)&reward_values;
    u32 collision_addr;

    ((Rec_func_800206D0_arg1 *)motion)->unk_00 += ((Rec_func_800206D0_arg1 *)motion)->unk_0C;
    ((Rec_func_800206D0_arg1 *)motion)->unk_04 += ((Rec_func_800206D0_arg1 *)motion)->unk_10;
    ((Rec_func_800206D0_arg1 *)motion)->unk_08 += ((Rec_func_800206D0_arg1 *)motion)->unk_14;
    ((S_800236BC_3 *)(((S_800236BC_1 *)object)->unk_00))->unk_62 |= 2;

    state = ((S_800236BC_1 *)object)->unk_04.s;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(sprite);
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 += 0x40000;
        ((S_800236BC_1 *)object)->unk_1D = 0;
        if (((Rec_func_800206D0_arg1 *)motion)->unk_08 < 0) {
            return;
        }
        SD_Call(0x501);
        ((Rec_func_800206D0_arg1 *)motion)->unk_08 = 0;
        ((S_800236BC_1 *)object)->unk_06.s = 15;
        ((Rec_func_800206D0_arg1 *)motion)->unk_0C = ((rand() % 320) - 64) << 12;
        ((Rec_func_800206D0_arg1 *)motion)->unk_10 = (rand() % 96 + 128) << 12;
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 = 0xFFF00000;
        ((S_800236BC_1 *)object)->unk_04.u++;
        return;

    case 1:
        advance_sprite_animation_and_textures(sprite);
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 += 0x40000;
        ((S_800236BC_1 *)object)->unk_06.u--;
        if (((Rec_func_800206D0_arg1 *)motion)->unk_08 < 0) {
            return;
        }
        SD_Call(0x501);
        if (((S_800236BC_1 *)object)->unk_06.s > 0) {
            ((Rec_func_800206D0_arg1 *)motion)->unk_08 = 0;
            ((Rec_func_800206D0_arg1 *)motion)->unk_14 = -((Rec_func_800206D0_arg1 *)motion)->unk_14;
            return;
        }
        ((Rec_func_800206D0_arg1 *)motion)->unk_08 = 0;
        ((Rec_func_800206D0_arg1 *)motion)->unk_10 = 0;
        ((Rec_func_800206D0_arg1 *)motion)->unk_0C = 0;
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 = ((rand() & 0xFF) << 11) - 0x150000;
        ((S_800236BC_1 *)object)->unk_06.s = (rand() & 0xF) + 30;
        ((S_800236BC_1 *)object)->unk_04.u++;
        return;

    case 2:
        advance_sprite_animation_and_textures(sprite);
        ((Rec_func_800206D0_arg1 *)motion)->unk_14 += 0x30000;
        ((S_800236BC_1 *)object)->unk_06.u--;
        collision_addr = 0x80020000;
        if (((Rec_func_800206D0_arg1 *)motion)->unk_08 >= 0) {
            ((Rec_func_800206D0_arg1 *)motion)->unk_08 = 0;
            if (((S_800236BC_1 *)object)->unk_06.s < 0) {
                sprite_data = D_800244DC[((S_800236BC_1 *)object)->unk_54];
                ((SpriteFrameState *)sprite)->clut = 0;
                ((SpriteFrameState *)sprite)->unk_04 = 0;
                ((SpriteFrameState *)sprite)->unk_05 = 0;
                ((SpriteFrameState *)sprite)->source = sprite_data;
                ((Rec_func_800206D0_arg1 *)motion)->unk_14 = 0;
                ((S_800236BC_1 *)object)->unk_06.s = 150;
                ((S_800236BC_1 *)object)->unk_04.u++;
            } else {
                ((Rec_func_800206D0_arg1 *)motion)->unk_14 = -((Rec_func_800206D0_arg1 *)motion)->unk_14 >> 1;
            }
        }
        collision_addr = (u32)&D_80024488;
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes((void *)collision_addr, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) == 0) {
            return;
        }
        SD_Call(0x516);
        {
            u8 *stack_base;
            stack_base = __builtin_alloca(0);
            reward_units = *(s32 *)(((S_800236BC_1 *)object)->unk_54 * 4 + stack_base);

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
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(D_80024488, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) == 0) {
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
        if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(D_80024488, motion, &D_800D0420, ((u8 *)(&view_reference_entity))) != 0) {
            SD_Call(0x516);
            reward_amount = reward_table[((S_800236BC_1 *)object)->unk_54] * 100;
            town_money[0] += reward_amount;
            pickup_reward_total[0] += reward_amount;
            ((S_800236BC_1 *)object)->unk_04.s = 255;
        }
        {
            s32 sprite_flags;
            if ((((S_800236BC_1 *)object)->unk_06.u >> 2) & 1) {
                sprite_flags = ((SpriteFrameState *)sprite)->flags | 0x80;
            } else {
                sprite_flags = ((SpriteFrameState *)sprite)->flags & 0xFF7F;
            }
            ((SpriteFrameState *)sprite)->flags = sprite_flags;
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
