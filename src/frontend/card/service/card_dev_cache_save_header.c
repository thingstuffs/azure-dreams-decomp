#include "frontend/card/save_slot.h"
#include "sdk/libc.h"
#include "common.h"
#include "frontend/card/service.h"

extern CardSaveSlot card_slot_header_cache[];

/* Copy 128 bytes from the source's offset 0x200 into an entry and mark it active. */
void card_dev_cache_save_header(s32 entry_index, void *source) {
    s32 *entry;

    entry = card_slot_header_cache[entry_index].words;
    memcpy(entry, (u8 *)source + 0x200, 0x80);
    card_slot_header_cache[entry_index].words[0] = 1;
}
