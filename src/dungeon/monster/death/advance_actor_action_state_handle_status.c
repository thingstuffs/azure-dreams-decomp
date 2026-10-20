#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80173CD4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_80173CD4_0;   /* arg0 in advance_actor_action_state_handle_status */

typedef struct S_80173CD4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173CD4_1;   /* arg2 in advance_actor_action_state_handle_status */

typedef struct S_80173CD4_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173CD4_2;   /* arg3 in advance_actor_action_state_handle_status */

typedef struct S_80173CD4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173CD4_4;   /* global in advance_actor_action_state_handle_status */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

/* Advance the actor action state, handle status flags, and update directional animation. */
void advance_actor_action_state_handle_status(void *action_in, void *context_in, void *sprite_in, void *actor_in)
{
    s32 state;

    u8 *world_state;
    u16 counter_value;

    state = ((S_80173CD4_0 *)action_in)->unk_9B;
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *world_counters;
        u8 *direction_anims;
        if (!(((S_80173CD4_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        direction_anims = D_80174684;
        (*(void * *)((u8 *)sprite_in + 0x2C)) = direction_anims;
        select_sprite_entry(sprite_in,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173CD4_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        world_counters = &g_dungeon_status;
        (*(u16 *)&world_counters->activity_counts.parts.pending_action_count)--;
    }
        ((S_80173CD4_0 *)action_in)->unk_9B++;
        return;
    case 1:
    {
        u32 world_page;
        u32 actor_flags;

        if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
            world_page = 0x80080000;
            world_state = (u8 *)((u32)&g_dungeon_status.turn_scale);
            if (((S_80173CD4_4 *)world_state)->unk_02 & 0x1000) {
                return;
            }

            if (((S_80173CD4_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action_in, context_in, sprite_in, 0) != 0) {
                    return;
                }
            }

            if (((S_80173CD4_2 *)actor_in)->unk_25 == 0) {
                if (((S_80173CD4_4 *)world_state)->unk_02 & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action_in, context_in, sprite_in, actor_in);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }

            actor_flags = ((S_80173CD4_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action_in, context_in, sprite_in, actor_in);
                return;
            }

            if (actor_flags & 0x80000) {
                u16 current_amount;
                u16 pending_amount;
                u32 packed_adjustment;

                begin_actor_move_to_target_facing(action_in, context_in, sprite_in, actor_in);
                current_amount = ((S_80173CD4_0 *)action_in)->unk_92;
                pending_amount = ((S_80173CD4_0 *)action_in)->unk_A4.at02.v;
                packed_adjustment = ((S_80173CD4_0 *)action_in)->unk_A4.at00.v;
                ((S_80173CD4_0 *)action_in)->unk_A4.at02.v = 0;
                ((S_80173CD4_0 *)action_in)->unk_B8 = 0;
                ((S_80173CD4_0 *)action_in)->unk_AC = 0;
                ((S_80173CD4_0 *)action_in)->unk_B0 = 0;
                ((S_80173CD4_0 *)action_in)->unk_92 = current_amount - pending_amount;
                ((S_80173CD4_0 *)action_in)->unk_A8 = packed_adjustment;
                func_801743F0(action_in, context_in, sprite_in, actor_in);
                return;
            }

            if (((S_80173CD4_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                if ((check_entity_relation(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
                TileObject *reference_pos;
                s8 room_id;

                reference_pos = &D_80082E80;
                room_id = ((S_80173CD4_1 *)sprite_in)->unk_26;
                if ((((room_id == reference_pos->room_index) &&
                      (room_id >= 0)) ||
                     (get_tile_chebyshev_distance(reference_pos, sprite_in) < 2)) &&
                    !(generate_random_value() & 7)) {
                    clear_slots_of_type(actor_in, 1);
                }
            }

            if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
                return;
            }
            {
                u8 *direction_anims;

                direction_anims = D_8017468C;
                (*(void * *)((u8 *)sprite_in + 0x2C)) = direction_anims;
                select_sprite_entry(sprite_in,
                    direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173CD4_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                    0);
                ((S_80173CD4_2 *)actor_in)->unk_1C |= 0x40000;
                if (((S_80173CD4_1 *)sprite_in)->unk_14 & 0x8000) {
                    ((S_80173CD4_0 *)action_in)->unk_8C = &D_801719DC;
                    return;
                }

                {
                    counter_value = (u16)g_dungeon_status.activity_counts.parts.pending_action_count;
                    counter_value++;
                    g_dungeon_status.activity_counts.parts.pending_action_count = counter_value;
                }
            }
            ((S_80173CD4_0 *)action_in)->unk_9B++;
            return;
        } else {
            {
                u8 *direction_anims;

                direction_anims = D_8017468C;
                (*(void * *)((u8 *)sprite_in + 0x2C)) = direction_anims;
                select_sprite_entry(sprite_in,
                    direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173CD4_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                    0);
                ((S_80173CD4_2 *)actor_in)->unk_1C |= 0x40000;
                if (((S_80173CD4_1 *)sprite_in)->unk_14 & 0x8000) {
                    ((S_80173CD4_0 *)action_in)->unk_8C = &D_801719DC;
                    return;
                }

                {
                    counter_value = (u16)g_dungeon_status.activity_counts.parts.pending_action_count;
                    counter_value++;
                    g_dungeon_status.activity_counts.parts.pending_action_count = counter_value;
                }
            }
            ((S_80173CD4_0 *)action_in)->unk_9B++;
            return;
        }
    }
    case 2:
        if (((S_80173CD4_1 *)sprite_in)->unk_14 & 0xE000) {
            counter_value = (u16)g_dungeon_status.activity_counts.parts.pending_action_count;
            counter_value--;
            g_dungeon_status.activity_counts.parts.pending_action_count = counter_value;
        } else {
            return;
        }
        ((S_80173CD4_0 *)action_in)->unk_8C = &D_801719DC;
        return;
    }
}

