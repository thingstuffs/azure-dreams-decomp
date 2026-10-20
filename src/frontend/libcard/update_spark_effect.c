#include "common.h"

extern void card_boot_set_slot_selection_marker(void *object_addr, s32 enable_table);
extern void advance_linked_object_counter(void *object, s32 value);
extern void card_boot_clear_slot_selection_marker(void *object_addr);
extern void card_boot_set_slot_details_selection(s32 object_addr, s32 value_7c, s32 value_80);

void update_spark_effect(void *menu)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == *(s32 *)((u8 *)menu + 0x2C)) {
            advance_linked_object_counter(((void **)menu)[index + 1], 1);
        } else if (index == *(s32 *)((u8 *)menu + 0x28)) {
            card_boot_set_slot_selection_marker(((void **)menu)[index + 1], 1);
        } else {
            card_boot_clear_slot_selection_marker(((void **)menu)[index + 1]);
        }
    }

    card_boot_set_slot_details_selection(
        *(s32 *)((u8 *)menu + 0x1C),
        *(s32 *)((u8 *)menu + 0x28),
        *(s32 *)((u8 *)menu + 0x44)
        );
}
