/* G00538: direction entry status. */
/* Original-file evidence (G00538): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0464, PD:town/engine:800D046C. */
#include "town/player/direction_entry_status_g00538.h"
#include "town/player.h"

/*
 * Converts held buttons to a camera-relative eight-way direction and searches four available slots
 * for a matching direction. Saves the entry and slot, returning -1 for entry type one, one for
 * another match, or zero when absent.
 */
s32 select_an_available_entry_matching_direction_returns_status(void *record_arg)
{
    Rec_D_800CFCB4 *record = record_arg;
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 entry_type;
    s32 special_type;
    s32 direction_index;
    S_8009567C_3 *entry;

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
                if (((S_8009567C_0 *)((u8 *)record + slot))->unk_3A != 0) {
                    entry = ((S_8009567C_1 *)((u8 *)record + slot * 4))->unk_1C;
                    record->unk_18 = slot;
                    record->unk_10 = entry;
                    entry_type = entry->unk_14;
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
s32 get_status_active_entry_matching_direction(void *entries)
{
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 state;
    s32 blocked_state;
    s32 entry_index;
    S_80095760_2 *entry;

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
                if (((S_80095760_0 *)((u8 *)entries + slot))->unk_3A != 0) {
                    entry = ((S_80095760_1 *)((u8 *)entries + slot * 4))->unk_1C;
                    state = entry->unk_14;
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
