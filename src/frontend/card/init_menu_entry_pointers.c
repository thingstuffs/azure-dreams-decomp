#include "common.h"
#include "frontend/card/menu_defaults.h"
#include "frontend/card.h"




/* Initialize entry pointers, per-entry defaults, and shared state defaults. */
void init_menu_entry_pointers(void *state, s32 entry_count) {
    s32 entry_index;

    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        *(u8 **) ((u8 *) state + 0x68C + entry_index * 4) = (u8 *) state + 0x6A4 + entry_index * 0x10;
        *(s32 *) ((u8 *) state + 0x704 + entry_index * 0x10) = menu_primitive_defaults[0];
        *(s32 *) ((u8 *) state + 0x708 + entry_index * 0x10) = menu_primitive_defaults[1];
        *(s32 *) ((u8 *) state + 0x70C + entry_index * 0x10) = menu_primitive_defaults[2];
        *(s32 *) ((u8 *) state + 0x710 + entry_index * 0x10) = menu_primitive_defaults[3];
        *(s32 *) ((u8 *) state + 0x6A8 + entry_index * 0x10) = (s32) ((u8 *) state + 0x704 + entry_index * 0x10);
        *(u8 **) ((u8 *) state + 0x6AC + entry_index * 0x10) = (u8 *) state + 0x670;
    }
    *(s32 *) ((u8 *) state + 0x670) = menu_settings_defaults[0];
    *(s32 *) ((u8 *) state + 0x674) = menu_settings_defaults[1];
    *(s32 *) ((u8 *) state + 0x678) = menu_settings_defaults[2];
}
