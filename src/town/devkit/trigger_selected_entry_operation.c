#include "common.h"
#include "town/shop/state.h"
#include "town/devkit.h"
extern u8 D_80700670[];

/* Call set_linked_flag_80700cd0 with 0x278 when the selected entry has bit zero set. */
void trigger_selected_entry_operation(s32 row, s32 column) {
    s32 offset = (column * 8) + (row * 16);

    if (*(s32 *)(D_80700670 + offset) & 1) {
        set_linked_flag_80700cd0(0x278);
    }
}
