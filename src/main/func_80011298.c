#include "common.h"
#include "m2c_compat.h"

void card_boot_populate_slot_window_display();                         /* extern */
void write_fixed_palette_pixels();                         /* extern */
void card_boot_clear_ten_display_slots();                         /* extern */

/* Runs three update routines on the data of a non-null object. */
void card_boot_refresh_slot_window(s32 object_addr) {
    s32 object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        write_fixed_palette_pixels(object_data);
        card_boot_clear_ten_display_slots(object_data);
        card_boot_populate_slot_window_display(object_data);
    }
}
