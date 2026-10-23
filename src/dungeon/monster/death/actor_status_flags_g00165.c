/* Actor status flags (G00165).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00165 - PD:dungeon/bank_be1000:8017468C, PD:dungeon/bank_be7000:8016E68C, PD:dungeon/bank_bed000:8016868C, PD:dungeon/bank_bf3000:8016268C, PD:dungeon/bank_bf9000:8015C68C, PD:dungeon/bank_bff000:8015668C.
 */
#include "dungeon/monster/death/actor_status_flags_g00165.h"
#include "dungeon/monster/death.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

/* Advance the actor action state, handle status flags, and update directional animation. */
void advance_actor_action_state_handle_status(void *action_in, void *context_in, SpriteFrameState *sprite_in, void *actor_in)
{
    s32 state;

    DungeonGlobalStatus *world_state;
    u16 counter_value;

    state = ((S_80173CD4_0 *)action_in)->unk_9B;
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *world_counters;
        u8 *direction_anims;
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        direction_anims = D_80174684;
        (sprite_in->frameTable) = direction_anims;
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
            if (world_state->flags & 0x1000) {
                return;
            }

            if (((S_80173CD4_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action_in, context_in, sprite_in, 0) != 0) {
                    return;
                }
            }

            if (((S_80173CD4_2 *)actor_in)->unk_25 == 0) {
                if (world_state->flags & 0x2008) {
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
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_mp(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
                TileObject *reference_pos;
                s8 room_id;

                reference_pos = &reference_tile_object;
                room_id = *(s8 *)&sprite_in->unk_26;
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
                (sprite_in->frameTable) = direction_anims;
                select_sprite_entry(sprite_in,
                    direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173CD4_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                    0);
                ((S_80173CD4_2 *)actor_in)->unk_1C |= 0x40000;
                if (sprite_in->flags & 0x8000) {
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
                (sprite_in ->frameTable) = direction_anims;
                select_sprite_entry(sprite_in,
                    direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173CD4_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                    0);
                ((S_80173CD4_2 *)actor_in)->unk_1C |= 0x40000;
                if (sprite_in->flags & 0x8000) {
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
        if (sprite_in->flags & 0xE000) {
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

/* Advance actor states and directional animations while handling entity flags. */
void advance_actor_states_and_entity_flags(void *actor, void *context, SpriteFrameState *animation, ActorRecord *entity)
{
    s32 state;

    state = ((S_8017409C_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        s32 *dungeon_state;
        u8 *direction_frames;

        if (!(animation->flags & 0xE000)) {
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        ((S_8017409C_2 *)dungeon_state)->unk_0A--;
        direction_frames = D_80174684;
        (animation->frameTable) = direction_frames;
        select_sprite_entry(animation,
            direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((S_8017409C_0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u8 *dungeon_state;
        u32 entity_flags;

        if (entity->mp != 0) {
            s32 *dungeon_state;

            (animation->frameTable) = D_8017468C;
            select_sprite_entry(animation,
                D_8017468C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            dungeon_state = &g_dungeon_status.turn_scale;
            ((S_8017409C_2 *)dungeon_state)->unk_0A++;
            ((S_8017409C_0 *)actor)->unk_9B++;
            return;
        }

        dungeon_state = (u8 *)&g_dungeon_status.turn_scale;
        if (((S_8017409C_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 actor_value;
            u16 value_delta;
            u32 packed_delta;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            actor_value = ((S_8017409C_0 *)actor)->unk_92;
            value_delta = ((S_8017409C_0 *)actor)->unk_A4.at02.v;
            packed_delta = ((S_8017409C_0 *)actor)->unk_A4.at00.v;
            ((S_8017409C_0 *)actor)->unk_A4.at02.v = 0;
            ((S_8017409C_0 *)actor)->unk_B8 = 0;
            ((S_8017409C_0 *)actor)->unk_AC = 0;
            ((S_8017409C_0 *)actor)->unk_B0 = 0;
            ((S_8017409C_0 *)actor)->unk_92 = actor_value - value_delta;
            ((S_8017409C_0 *)actor)->unk_A8 = packed_delta;
            func_801743F0(actor, context, animation, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp == 0) {
            return;
        }

        (animation->frameTable) = D_8017468C;
        select_sprite_entry(animation,
            D_8017468C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&entity->flags1C) |= 0x40000;
        ((S_8017409C_4 *)dungeon_state)->unk_0A++;
    }
        ((S_8017409C_0 *)actor)->unk_9B++;
        return;
    case 2:
        if (animation->flags & 0xE000) {
            s32 *dungeon_state;

            dungeon_state = &g_dungeon_status.turn_scale;
            ((S_8017409C_2 *)dungeon_state)->unk_0A--;
            ((S_8017409C_0 *)actor)->unk_8C = &D_801719DC;
        }

        return;
    default:
        return;
    }
}
