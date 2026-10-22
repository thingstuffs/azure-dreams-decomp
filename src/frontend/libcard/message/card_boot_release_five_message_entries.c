#include "common.h"
#include "frontend/libcard/message.h"
void noop_release_notification(s32);                         /* extern */

typedef struct S_80023194_0 {
    u8 pad_00[0x8CC];
    s32 * unk_8CC;
} S_80023194_0;

/* Processes the values referenced by five consecutive record entries. */
void card_boot_release_five_message_entries(void *record) {
    s32 *value_ptr;
    s32 entry_index;
    void *entry_cursor;

    entry_index = 0;
    entry_cursor = record;
    do {
        value_ptr = ((S_80023194_0 *)entry_cursor)->unk_8CC;
        entry_cursor += 4;
        entry_index += 1;
        noop_release_notification(*value_ptr);
    } while (entry_index < 5);
}
