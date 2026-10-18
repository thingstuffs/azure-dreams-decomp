#include "common.h"
#include "m2c_compat.h"

void card_boot_set_paired_choice_selection(s32 object_addr, s32 value);                         /* extern */

typedef struct S_80027DF4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x14];
    s32 unk_24;
} S_80027DF4_0;

/* Sets an object's state value and passes its linked value to card_boot_set_paired_choice_selection. */
void card_boot_set_menu_and_panel_selection(s32 object_addr, s32 state_value) {
    S_80027DF4_0 *state;

    if (object_addr != 0) {
        state = object_addr + 0x20;
        state->unk_0C = state_value;
        card_boot_set_paired_choice_selection(state->unk_24, state_value);
    }
}
