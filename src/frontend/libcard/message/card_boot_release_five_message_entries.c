#include "common.h"
#include "frontend/libcard/message.h"
#include "slus.h"

/* Release the text of the dialog's first five display entries. */
void card_boot_release_five_message_entries(CardMessageDialogBody *record) {
    s32 entry_index;

    entry_index = 0;
    do {
        noop_release_notification(record->entries[entry_index]->payload.word);
        entry_index += 1;
    } while (entry_index < 5);
}
