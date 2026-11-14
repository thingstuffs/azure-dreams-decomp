/* Paired entry update and its file-private helper. */
#include "common.h"
#include "m2c_compat.h"
#include "town/shop.h"
/* Sets one of two linked entries to RGB 0x80 and the other to 0x40 according to the source state. */
static void set_paired_entry_brightness(void *object) {
    void **dim_entry;
    void **bright_entry;
    u8 *bright_rgb;
    u8 *dim_rgb;
    if (*((s32 *)(*(void ***)object) + 3) == 0) {
        void *first_entry;
        void *second_entry;

        dim_entry = *(void ***)((u8 *)object + 0x5C);
        first_entry = *dim_entry;
        second_entry = *(dim_entry + 1);
        bright_entry = first_entry;
        dim_entry = second_entry;
    } else {

        dim_entry = *(void ***)((u8 *)object + 0x5C);
        bright_entry = *(dim_entry + 1);
        dim_entry = *dim_entry;
    }
    {
        bright_rgb = *(bright_entry + 1);
        dim_rgb = *(dim_entry + 1);
        bright_rgb[0] = 0x80;
        bright_rgb[1] = 0x80;
        bright_rgb[2] = 0x80;
        dim_rgb[0] = 0x40;
        dim_rgb[1] = 0x40;
        dim_rgb[2] = 0x40;
    }
}

/*
 * Processes the entry lookup and expired resource countdowns, then updates paired entry brightness
 * for the same entry ID.
 */
void update_entry_resources_and_brightness(s32 entry_id) {
    apply_input_choice_value(entry_id);
    fade_choice_slot_colors(entry_id);
    set_paired_entry_brightness(entry_id);
}
