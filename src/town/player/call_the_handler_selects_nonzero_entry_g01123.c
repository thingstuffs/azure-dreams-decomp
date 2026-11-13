/* Call the handler selects nonzero entry g01123.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_80097264, CL:town/func_80097300.
 */
#include "town/player/call_the_handler_selects_nonzero_entry_g01123.h"
#include "town/player.h"
#include "engine/graphics.h"

/* Call the handler when the record selects a nonzero entry. */
void dispatch_selected_entry_if_nonzero(s32 *entries, TownObjectRecord *record, void *ptr2) {
    if (entries[record->unk_16] != 0) {
        forward_selected_entry_value(entries, record, ptr2);
    }
}

/*
 * Selects a sprite frame through the view-relative angle sector and adds two divided by
 * animation_tick_scale to destination byte 5.
 */
void set_sprite_frame_by_view_angle(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = view_relative_angle_sector(selection);
    set_sprite_animation_frame(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)animation_tick_scale);
}

/* Stores the value in the record and forwards it with unk_10 to set_sprite_frame_by_view_angle. */
void store_entry_and_set_frame(s32 value, Rec_D_80082D58 *record, void *destination) {
    record->unk_1C = value;
    set_sprite_frame_by_view_angle((u8 *)value, record->unk_10, destination);
}

/* Passes the selected nonzero table value to store_entry_and_set_frame. */
void forward_selected_entry_value(s32 *values, TownObjectRecord *selector, void *ptr2) {
    s32 value = values[selector->unk_16];
    if (value != 0) {
        store_entry_and_set_frame(value, (Rec_D_80082D58 *) selector, ptr2);
    }
}
