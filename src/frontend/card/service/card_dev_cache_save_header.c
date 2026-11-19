#include "frontend/card/save_slot.h"
#include "sdk/libc.h"
#include "common.h"
#include "frontend/card/service.h"


/* Copy 128 bytes from the source's offset 0x200 into an entry and mark it active. */
void card_dev_cache_save_header(s32 entry_index, void *source) {
    CardSaveSlot *entry;

    entry = &card_slot_header_cache[entry_index];
    memcpy(entry, (u8 *)source + 0x200, sizeof(*entry));
    card_slot_header_cache[entry_index].fields.marker = 1;
}
