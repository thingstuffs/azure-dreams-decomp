#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_ids.h"
/* Linked entity state (G00259).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00259 - CL:dungeon/func_80E3A540@dungeon/bank_e56c58, CL:dungeon/func_80E3A540@dungeon/bank_e5d000, CL:dungeon/func_80E3A540@dungeon/bank_e63000, CL:dungeon/func_80E3A540@dungeon/bank_e69000, CL:dungeon/func_80E3A540@dungeon/bank_e6f000, CL:dungeon/func_80E3A540@dungeon/bank_e75000.
 */
#include "dungeon/monster/manoeva/linked_entity_state_g00259.h"

/* Copies linked object data and transfers or releases its state. */
void transfer_linked_object_state(ActorRecord *owner, ObjectPosition *object_id, SpriteFrameState *dest_object, ActorRecord *dest_state) {
    u8 *linked_object;
    u8 *linked_state;
    u8 *source_object;
    u8 *state_slot;
    ActorRecord *state_table;
    u8 *kind_entry;
    s32 call_result;
    u8 kind_unlisted;
    u8 can_release;
    s32 state_kind;
    u8 kind_byte;
    long slot_address;

    linked_object = *(u8 **)(((u8 *)owner + 0xA4));
    linked_state = linked_object + 0x20;
    source_object = *(u8 **)(linked_object + 0xC);
    dest_object->tile_x = source_object[0x24];
    dest_object->tile_y = source_object[0x25];
    dest_state->ground_height = *(u16 *)(linked_state + 0x88);
    set_record_integer_tile_center(object_id, dest_object->tile_x, dest_object->tile_y);

    linked_object = *(u8 **)(((u8 *)owner + 0xA4));
    if (*(u16 *)(linked_object + 0x1E) & 0x8000) {
        if ((linked_state[0x13] == 0x1E) && (linked_state[0x28] != 0)) {
            dest_state->pending_turn_updates = 1;
        }

        if (dest_state->flags14 & 0x4000) {
            call_result = find_entity_slot_by_field_ac(linked_state);
            state_table = dungeon_actor_ring_anchor;
            slot_address = (s32)(s16)call_result * 4;
            slot_address += (long)state_table;
            state_slot = (u8 *)slot_address;
            *(u8 **)(state_slot + 0xAC) = dest_state;
            *(s32 *)(state_slot + 0xE4) = 0;
            if (((u8 *)state_table->target) == linked_state) {
                state_table->target = dest_state;
            }
        }

        /*
         * BUG: Oleem removes a living item-form Manoeva without reserving its reappearance. This test skips
         * the extra count, but both the fade-in and pentagram later decrement it, leaving -1 until the watchdog resets
         * it.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        if ((linked_state[0x13] != 0x1E) && (linked_state[0x28] == 0)) {
            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }

        dest_state->flags14 = 0;
        dest_state->flags1C = 0;
        copy_entity_record(dest_state, linked_state);
        (*(u32 *)&dest_state->flags14) &= 0xDFFFFFFF;
        call_result = get_entity_effect_value(dest_state, STATUS_SLEEP);
        if ((call_result << 16) != 0) {
            (*(u32 *)&dest_state->flags1C) |= 0x200;
        } else {
            (*(u32 *)&dest_state->flags1C) &= ~0x200;
        }

        dest_state->species = 0x1E;
        clear_entry_flag_and_link_owner(((u8 *)owner - 0x20));
        *(u32 *)(((u8 *)dest_state + 0x60)) = *(u32 *)(linked_state + 0x60);
        reset_linked_entity_state((S_80173D40_0 *)owner, object_id, (S_80173D40_1 *)dest_object, (EntityRec *)dest_state);
        owner->unk_A4.value = 0;
        return;
    }

    if ((((s8)linked_state[0x13] - 1) < 0) ||
        (linked_state[0x13] == 0x1E) ||
        (owner->action_phase.u != 0)) {
        return;
    }

    state_kind = linked_object[0x33];
    kind_byte = state_kind;
    kind_entry = find_monster_entry_by_type_and_id(kind_byte, 1);
    if (kind_entry == 0) {
        kind_unlisted = 1;
    } else {
        kind_unlisted = kind_entry[1] != kind_byte;
    }
    can_release = kind_unlisted;
    if (can_release == 0) {
        return;
    }

    kind_entry = find_monster_entry_by_type_and_id(state_kind, 3);
    if ((kind_entry != 0) && (kind_entry[1] == state_kind)) {
        kind_unlisted = 0;
    }
    can_release = kind_unlisted;
    if (can_release == 0) {
        return;
    }

    if (g_dungeon_status.active_actor == linked_state) {
        g_dungeon_status.active_actor = 0;
    }
    begin_actor_flagged_action(linked_state, *(s32 *)(linked_state - 0x18),
                  *(s32 *)(linked_state - 0x14), linked_state);
    owner->action_phase.u++;
}

/*
 * Starts Manoeva's directional action when dungeon activity permits, marks its state, and
 * increments the activity count.
 */
void initialize_object_and_clear_state(ActorRecord *action, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *entity) {

    if (g_dungeon_status.flags & 0x2000) {
        entity->movement_queue_state &= 0x7F;
        return;
    }

    if ((has_pending_dungeon_activity(entity) << 16) == 0) {
        s32 direction;

        action->action_id.s = 0x17;
        action->action_phase.s = 0;
        ((S_80173C40_2 *)action)->unk_8C = 0;
        animation->frameTable = D_80176670;

        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        select_sprite_entry(animation, D_80176670[direction], 0);

        action->action_timer.s = 0;
        entity->flags1C |= 0x10000000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        entity->action_flags &= 0x7FFF;
    }
}

/* Resets state to code 0x19 and updates the associated record flags. */
void reset_linked_entity_state(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *flag_record, ActorRecord *record) {
    state->action_id.u = 0x19;
    state->action_phase.u = 0;
    state->unk_8C.handler = 0;
    flag_record->flags = (u16) (flag_record->flags & 0xF7FF);
    state->action_timer.u = 0;
    record->flags1C = (s32) (record->flags1C | 0x10000000);
}
