#include "sdk/libc.h"
#include "common.h"
#include "frontend/card/service.h"

extern s32 card_slot_header_cache[][32];

/* Copy 128 bytes from the source's offset 0x200 into an entry and mark it active. */
void card_dev_cache_save_header(s32 entry_index, void *source) {
    s32 *entry;

    entry = card_slot_header_cache[entry_index];
    memcpy(entry, (u8 *)source + 0x200, 0x80);
    card_slot_header_cache[entry_index][0] = 1;
}
