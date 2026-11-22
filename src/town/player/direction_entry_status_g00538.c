/* direction entry status. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0464, PD:town/engine:800D046C. */
#include "town/player/direction_entry_status_g00538.h"
#include "town/player.h"

/*
 * Converts held buttons to a camera-relative eight-way direction and searches four available slots
 * for a matching direction. Saves the entry and slot, returning -1 for entry type one, one for
 * another match, or zero when absent.
 */
s32 select_entry_by_input_direction(ColliderView *record)
{
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 entry_type;
    s32 special_type;
    s32 direction_index;
    ColliderView *entry;

    angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
    if (angle != -1) {
        direction_index = 0;
        direction = ((angle + 0x100) / 0x200) & 7;
        special_type = 1;
        slot_ptr = D_800D046C;
        direction_ptr = D_800D0464;
        do {
            if (direction == *direction_ptr) {
                slot = *slot_ptr;
                if (record->pending_flags[slot] != 0) {
                    entry = record->slots[slot];
                    record->selected_face = slot;
                    record->selected_entry = entry;
                    entry_type = entry->mode;
                    if (entry_type == special_type) {
                        return -1;
                    }
                    return 1;
                }
            }
            slot_ptr++;
            direction_index++;
            direction_ptr++;
        } while (direction_index < 4);
    }
    return 0;
}

/* Returns the status of the active entry matching the current direction. */
s32 get_status_active_entry_matching_direction(ColliderView *entries)
{
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 state;
    s32 blocked_state;
    s32 entry_index;
    ColliderView *entry;

    angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
    if (angle != -1) {
        entry_index = 0;
        direction = ((angle + 0x100) / 0x200) & 7;
        blocked_state = 1;
        slot_ptr = D_800D046C;
        direction_ptr = D_800D0464;
        do {
            if (direction == *direction_ptr) {
                slot = *slot_ptr;
                if (entries->pending_flags[slot] != 0) {
                    entry = entries->slots[slot];
                    state = entry->mode;
                                         /* MATCH: preserve the loop pointers' live ranges through the byte load after removing the label call. */
                    if (state == blocked_state) {
                        return -1;
                    }
                    return 1;
                }
            }
            slot_ptr++;
            entry_index++;
            direction_ptr++;
        } while (entry_index < 4);
    }
    return 0;
}
