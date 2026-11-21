#include "common.h"
#include "shared/timed_stream.h"

#include "frontend/libcard/paired_choice.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "slus.h"

/* Updates or clears active records, then refreshes the object if any were active. */
void card_boot_set_paired_choice_animations(CardChoiceOwner *object, s32 *enable_flags, s32 *active_flags)
{
    s32 *slot_value;
    s32 slot_index;
    s32 updated;

    updated = 0;
    for (slot_index = 0; slot_index < 2; slot_index++) {
        if (active_flags[slot_index] != 0) {
            slot_value = &object->pointers[2 + slot_index]->payload.word;
            updated = 1;
            if (enable_flags[slot_index] != 0) {
                initialize_scaled_entry_cursor(&object->choice_cursors[slot_index], &card_choice_cursor_data, slot_value);
            } else {
                *slot_value = 0;
                object->choice_cursors[slot_index].output = 0;
            }
        }
    }
    if (updated != 0) {
        card_boot_refresh_paired_choice_labels(object);
    }
}
