/* Callback position updates (G00373). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D6EF0, CL:dungeon/func_800D6FC4, CL:dungeon/func_800D70CC, PD:dungeon/engine:800E2934. */
#include "dungeon/menu/callback_position_updates_g00373.h"
#include "dungeon/menu.h"

/* Moves the current value toward its selected target and updates the object state. */
void move_value_toward_target(u8 *object_data, s32 unused_coord, s32 unused_y) {
    u8 *state;
    u32 flags;
    s32 current;
    s32 target;
    s32 delta;
    u32 mode;
    void *handle;
    s32 result;

    state = object_data + 0x3C;
    flags = *(u32 *)(object_data + 0x50);
    current = *(s16 *)(*(u8 **)(state + 8) + 0xE);
    target = *(s16 *)((u8 *)D_800E2934 + (flags & 2));
    delta = target - current;

    if (delta < 0) {
        if (delta >= -0x80) {
            current = target;
        } else {
            current -= 0x80;
        }
    } else {
        if (delta < 0x81) {
            current = target;
        } else {
            current += 0x80;
        }
    }

    if (current != target) {
        *(s32 *)(object_data + 0x58) = 1;
        handle = *(void **)(object_data + 0x3C);
        mode = 0;
    } else {
        mode = *(u32 *)(object_data + 0x50);
        handle = *(void **)(object_data + 0x3C);
        mode = mode >> 1;
        mode = mode ^ 1;
        mode = mode % 2;
    }
    result = link_indexed_entry_chain(handle, mode);
    do {
        dungeon_menu_object->value = result;
    } while (0);
    set_object_value_and_negation(state, current);
}

/* Move toward the indexed position, then apply the pending index once settled. */
void move_indexed_position_and_apply(S_800DC724_0 *state)
{
    s32 coord;
    s32 next_index;
    s32 delta_x;
    s32 delta_y;
    s32 current_index;
    s32 biased_dx;
    s32 biased_dy;
    s32 target_y;
    s32 index;
    s32 target_x;
    u8 *positions;
    S_800DC724_2 *holder;
    S_800DC724_3 *position;
    S_800DC724_1 *target;

    positions = D_800E2924;
    index = state->unk_50;
    holder = state->unk_3C;
    target = (index * 4) + positions;
    target_x = target->unk_00;
    target_y = target->unk_02;
    position = holder->unk_04;
    state->unk_58 = 0;
    delta_x = (s16)target_x - position->unk_08;
    if (delta_x != 0) {
        state->unk_58 = 1;
        coord = position->unk_08;
        biased_dx = delta_x > 0 ? delta_x + 3 : delta_x - 3;
        position->unk_08 = coord + (biased_dx >> 2);
    }
    delta_y = (s16)target_y - position->unk_0A;
    if (delta_y != 0) {
        state->unk_58 = 1;
        coord = position->unk_0A;
        biased_dy = delta_y > 0 ? delta_y + 3 : delta_y - 3;
        position->unk_0A = coord + (biased_dy >> 2);
    }
    move_value_toward_target(state, coord, target_y);
    if (state->unk_58 != 0) {
        return;
    }
    current_index = state->unk_50;
    next_index = state->unk_54;
    if (current_index == next_index) {
        return;
    }
    if ((next_index ^ current_index) & 2) {
        SD_Call(0x507);
    }
    state->unk_50 = state->unk_54;
}

/* Updates the low flag bits and activity field from the referenced state. */
void update_state_activity_flags(S_800DC82C_0 *record) {
    s32 state_or_flags;
    s32 flag_value;

    record->unk_5C = 0;
    state_or_flags = *record->unk_38;
    flag_value = 1;
    if (state_or_flags == 0) {
        state_or_flags = record->unk_54;
        state_or_flags |= 3;
    } else if (state_or_flags == flag_value) {
        state_or_flags = record->unk_54;
        flag_value = -3;
        state_or_flags |= 1;
        state_or_flags &= flag_value;
    } else {
        state_or_flags = record->unk_54;
        record->unk_5C = flag_value;
        flag_value = -2;
        state_or_flags &= flag_value;
        flag_value = -3;
        state_or_flags &= flag_value;
    }
    record->unk_54 = state_or_flags;
}

/* Advances the menu's referenced cycle index modulo three and updates its activity flags. */
void advance_wrapped_cycle_index(void) {
    s32 *cycleIndexToWrap;
    s32 *cycleIndexToIncrement;
    s32 incrementedIndex;
    S_800DC888_0 *cycleState;

    cycleState = (S_800DC888_0 *)((s32)dungeon_menu_object + 0x20);
    cycleIndexToIncrement = cycleState->unk_38;
    *cycleIndexToIncrement += 1;
    cycleIndexToWrap = cycleState->unk_38;
    incrementedIndex = *cycleIndexToWrap;
    *cycleIndexToWrap = incrementedIndex % 3;
    update_state_activity_flags(cycleState);
}

/* Runs callbacks for slots 1 through 7, then processes the object and its final callback. */
void process_callback_slots_and_object(u8 *object) {
    s32 slot;
    FinalFunc final_callback;

    for (slot = 1; slot < 8; slot++) {
        D_800E2934[slot](object, *(s32 *)(object + 0x3C) + slot * 0x10);
    }
    move_indexed_position_and_apply(object);
    final_callback = *(FinalFunc *)(object + 0x4C);
    if (final_callback != 0) {
        final_callback(object);
    }
}
