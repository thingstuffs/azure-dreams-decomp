#include "common.h"
#include "shared/timed_stream.h"

typedef struct Object13B18 {
    s32 unk_00;
    FrameState records[2]; /* the two choice cursor streams initialize_scaled_entry_cursor starts */
    u8 pad_1C[0x4C];
    s32 *slots[2];
} Object13B18;   /* object in card_boot_set_paired_choice_animations */

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "slus.h"
extern FrameNode card_choice_cursor_data;

/* Updates or clears active records, then refreshes the object if any were active. */
void card_boot_set_paired_choice_animations(Object13B18 *object, s32 *enable_flags, s32 *active_flags)
{
    s32 *slot_value;
    s32 slot_index;
    s32 updated;

    updated = 0;
    for (slot_index = 0; slot_index < 2; slot_index++) {
        if (active_flags[slot_index] != 0) {
            slot_value = object->slots[slot_index];
            updated = 1;
            if (enable_flags[slot_index] != 0) {
                initialize_scaled_entry_cursor(&object->records[slot_index], &card_choice_cursor_data, slot_value);
            } else {
                *slot_value = 0;
                object->records[slot_index].output = 0;
            }
        }
    }
    if (updated != 0) {
        card_boot_refresh_paired_choice_labels(object);
    }
}
