#include "common.h"
#include "shared/town_handler.h"

void set_sprite_animation_frame();
s32 view_relative_angle_sector();
extern u8 D_80080A84;

/* Applies a selected source byte to the destination and adjusts its sixth byte. */
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = view_relative_angle_sector(selection);
    set_sprite_animation_frame(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)D_80080A84);
}
