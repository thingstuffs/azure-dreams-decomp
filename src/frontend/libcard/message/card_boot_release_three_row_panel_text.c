#include "common.h"
#include "frontend/libcard/message.h"

void noop_release_notification(s32 value);

typedef struct S_800239B0_0 {
    u8 pad_00[0x1D8];
    s32 * unk_1D8;
} S_800239B0_0;

/* Processes the values referenced by three consecutive record entries. */
void card_boot_release_three_row_panel_text(void *record) {
    s32 *value_ptr;
    s32 entry_index;
    void *entry_cursor;

    entry_index = 0;
    entry_cursor = record;
    do {
        value_ptr = ((S_800239B0_0 *)entry_cursor)->unk_1D8;
        entry_cursor += 4;
        entry_index += 1;
        noop_release_notification(*value_ptr);
    } while (entry_index < 3);
}
