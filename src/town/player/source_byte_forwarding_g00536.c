/* G00536: source byte forwarding. */
/* Original-file evidence (G00536): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80097264, CL:town/func_80097300. */
#include "town/player/source_byte_forwarding_g00536.h"

/* Applies a selected source byte to the destination and adjusts its sixth byte. */
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = view_relative_angle_sector(selection);
    set_sprite_animation_frame(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)D_80080A84);
}

/* Stores the value in the record and forwards it with unk_10 to apply_a_selected_source_byte_destination_adjusts_sixth_byte. */
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, void *destination) {
    record->unk_1C = value;
    apply_a_selected_source_byte_destination_adjusts_sixth_byte((u8 *)value, record->unk_10, destination);
}
