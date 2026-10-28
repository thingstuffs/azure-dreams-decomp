#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Actor status events (G00019).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00019 - PD:dungeon/bank_1025000:801748E8, PD:dungeon/bank_102b000:8016E8E8, PD:dungeon/bank_1031000:801688E8, PD:dungeon/bank_1037000:801628E8, PD:dungeon/bank_103d000:8015C8E8, PD:dungeon/bank_1043000:801568E8.
 */
#include "dungeon/monster/garuda/actor_status_events_g00019.h"
#include "dungeon/monster/garuda.h"
#include "shared/sprite_frame_state.h"

/* Updates actor state, animation, and callback according to entity status flags. */
void update_actor_status_callback(void *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite_in, void *entity_in) {
    void *context = context_in;
    s32 status_flags;
    u16 current_value;
    u16 value_adjustment;
    u8 *page_base;
    s32 state;

    state = ((S_801730B4_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        (sprite_in->frameTable) = garuda_frame_set_2;
        select_sprite_entry(sprite_in,
            garuda_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730B4_2 *)entity_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            u16 counter_value;

            counter_value = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            counter_value--;
            g_dungeon_status.activity_counts.parts.pending_action_count = counter_value;
        }
        ((S_801730B4_0 *)actor_in)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(entity_in, STATUS_SLEEP) << 16) == 0) {
            (sprite_in->frameTable) = garuda_frame_set_1;
            select_sprite_entry(sprite_in,
                garuda_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730B4_2 *)entity_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801730B4_2 *)entity_in)->unk_1C.s |= 0x40000;
            if (!(sprite_in->flags & 0x8000)) {

                state = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
                state++;
                g_dungeon_status.activity_counts.parts.pending_action_count = state;
                ((S_801730B4_0 *)actor_in)->unk_9B++;
                return;
            }
            ((S_801730B4_2 *)entity_in)->unk_1C.s &= ~0x200;
            ((S_801730B4_0 *)actor_in)->unk_8C = garuda_action_resume_address;
            return;
        }
        page_base = (u8 *)0x80080000;
        {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (((S_801730B4_2 *)entity_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor_in, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((S_801730B4_2 *)entity_in)->unk_25 == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(actor_in, context, sprite_in, entity_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(entity_in) << 16) != 0) {
                return;
            }
            status_flags = ((S_801730B4_2 *)entity_in)->unk_1C.u;
            if (status_flags & 0x100) {
                begin_pushed_actor_move(actor_in, context, sprite_in, entity_in);
                return;
            }
            if (status_flags & 0x80000) {

                begin_actor_move_to_target_facing(actor_in, context, sprite_in, entity_in);
                current_value = ((S_801730B4_5 *)actor_in)->unk_92;
                value_adjustment = ((S_801730B4_5 *)actor_in)->unk_A6;
                ((S_801730B4_5 *)actor_in)->unk_A6 = 0;
                ((S_801730B4_5 *)actor_in)->unk_B2 = 0;
                ((S_801730B4_5 *)actor_in)->unk_92 = current_value - value_adjustment;
                func_80173834(actor_in, context, sprite_in, entity_in);
                return;
            }
            if (((S_801730B4_2 *)entity_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(entity_in) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = owner->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(entity_in,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(entity_in);
            on_actor_status_updated(entity_in);
            if ((get_entity_effect_value(entity_in, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&sprite_in->room_index;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite_in) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(entity_in, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(entity_in, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }
        (sprite_in->frameTable) = garuda_frame_set_1;
        select_sprite_entry(sprite_in,
            garuda_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730B4_2 *)entity_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            u32 updated_flags;

            updated_flags = ((S_801730B4_2 *)entity_in)->unk_1C.s;
            updated_flags |= 0x40000;
            ((S_801730B4_2 *)entity_in)->unk_1C.s = updated_flags;
        }
        if (sprite_in->flags & 0x8000) {
            ((S_801730B4_2 *)entity_in)->unk_1C.u &= ~0x200;
            ((S_801730B4_0 *)actor_in)->unk_8C = garuda_action_resume_address;
            return;
        }

        {

            state = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            state++;
            g_dungeon_status.activity_counts.parts.pending_action_count = state;
        }

        ((S_801730B4_0 *)actor_in)->unk_9B++;
        return;

    case 2:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((S_801730B4_2 *)entity_in)->unk_1C.u &= ~0x200;

        ((S_801730B4_0 *)actor_in)->unk_8C = garuda_action_resume_address;

        return;

    default:
        return;
    }
}

/* Advance the entity state, updating directional sprites and handling actor events. */
void advance_entity_directional_events(void *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;

    state = ((S_801734E0_0 *)entity)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_table;

        if (!(sprite->flags & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_table = garuda_frame_set_2;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801734E0_0 *)entity)->unk_9B++;
        return;
    }

    case 1:
    {
        u32 actor_flags;

        if (actor->mp_value.parts.whole != 0) {

            (sprite->frameTable) = garuda_frame_set_1;
            select_sprite_entry(sprite,
                garuda_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((S_801734E0_0 *)entity)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((u32)actor->flags1C);
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(entity, context, sprite, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            u16 previous_total;
            u16 pending_decrease;

            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            previous_total = ((S_801734E0_0 *)entity)->unk_92;
            pending_decrease = ((S_801734E0_0 *)entity)->unk_A6;
            ((S_801734E0_0 *)entity)->unk_A6 = 0;
            ((S_801734E0_0 *)entity)->unk_B2 = 0;
            ((S_801734E0_0 *)entity)->unk_92 = previous_total - pending_decrease;
            func_80173834(entity, context, sprite, actor);
            return;
        }

        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            {
                ObjectNodeHeader *previous_node;
                void *previous_body;
                ActorRecord *previous_actor;

                previous_node = primary_actor_record->previous_actor_header;
                previous_body = previous_node + 1;
                previous_actor = previous_body;
                if ((check_entity_relation(actor,
                        previous_actor) << 16) != 0) {
                    return;
                }
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if (actor->mp_value.parts.whole == 0) {
            return;
        }

        (sprite->frameTable) = garuda_frame_set_1;
        select_sprite_entry(sprite,
            garuda_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }

        ((S_801734E0_0 *)entity)->unk_9B++;
        return;
    case 2:
        if (sprite->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            actor->flags1C &= ~(ACTOR_MP_EMPTY | ACTOR_ASLEEP);
            ((S_801734E0_0 *)entity)->unk_8C = &garuda_action_resume_address;
        }

        return;
    }
}
