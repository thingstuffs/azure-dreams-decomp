#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"

extern void save_object_value_and_set_control_fields(s32 object, s32 new_value);

/* Updates the five save-slot selection markers and the object displaying the selected index. */
void card_devkit_refresh_save_slot_selection(void *menu) {
    s32 sentinel;
    s32 i;

    if (*(s32 *)((u8 *)menu + 0x48) == 1) {
        sentinel = 1;
    } else {
        save_object_value_and_set_control_fields(*(s32 *)((u8 *)menu + 0x18), *(s32 *)((u8 *)menu + 0x44));
        sentinel = 0;
    }
    i = 0;
    while (1) {
        if (i == *(s32 *)((u8 *)menu + 0x28)) {
            card_devkit_set_window_selection_marker(*(s32 *)((u8 *)menu + i * 4 + 4), sentinel);
        } else {
            card_dev_reset_object_tint(*(s32 *)((u8 *)menu + i * 4 + 4));
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    card_info_set_value_and_refresh(*(s32 *)((u8 *)menu + 0x1C), *(s32 *)((u8 *)menu + 0x28));
}
