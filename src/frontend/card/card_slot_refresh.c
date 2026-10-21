/* Clear the selection marker and refresh the card slot window. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

typedef struct S_80024274_0 {
    u8 pad_00[0x224];
    s32 unk_224;
    u8 pad_228[0x58];
    s32 * unk_280;
} S_80024274_0;

/* Initialize the object's embedded state and clear its referenced word. */
void card_boot_clear_slot_selection_marker(s32 object_addr) {
    S_80024274_0 *state;

    if (object_addr != 0) {
        state = object_addr + 0x20;
        state->unk_224 = 0x606868;
        *state->unk_280 = 0;
    }
}

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
