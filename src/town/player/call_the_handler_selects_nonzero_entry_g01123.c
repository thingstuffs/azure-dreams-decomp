/* Call the handler selects nonzero entry g01123.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01123 - CL:town/func_80097264, CL:town/func_80097300.
 */
#include "town/player/call_the_handler_selects_nonzero_entry_g01123.h"

/* Call the handler when the record selects a nonzero entry. */
void call_the_handler_selects_nonzero_entry(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2) {
    if (entries[record->unk_16] != 0) {
        call_the_selected_nonzero_table_callee_80094_a_38(entries, (S_80094A60_0 *)record, ptr2);
    }
}

/* Applies a selected source byte to the destination and adjusts its sixth byte. */
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = view_relative_angle_sector(selection);
    set_sprite_animation_frame(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)animation_tick_scale);
}

/* Stores the value in the record and forwards it with unk_10 to apply_a_selected_source_byte_destination_adjusts_sixth_byte. */
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, void *destination) {
    record->unk_1C = value;
    apply_a_selected_source_byte_destination_adjusts_sixth_byte((u8 *)value, record->unk_10, destination);
}

/* Passes the selected nonzero table value to store_the_in_forwards_field_10_callee_800949_c_4. */
void call_the_selected_nonzero_table_callee_80094_a_38(s32 *values, S_80094A60_0 *selector, void *ptr2) {
    s32 value = values[selector->unk_16];
    if (value != 0) {
        store_the_in_forwards_field_10_callee_800949_c_4(value, (Rec_D_80082D58 *) selector, ptr2);
    }
}
