#include "frontend/card/save_image.h"
#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"
#include "sdk/memory.h"



/* Copies 128 bytes from the source's offset 0x200 into a table entry and marks it active. */
void card_boot_cache_save_header(s32 entry_index, CardSaveImage *source) {
    const u8 *header = (const u8 *)source + 0x200;
    CardSaveSlot *base;
    s32 *entry;
    CardSaveSlot *final_base;
    s32 *final_entry;
    s32 initial_offset;
    s32 final_offset;

    base = card_save_slot_metadata;
    initial_offset = entry_index << 7;
    entry = (s32 *)(initial_offset + (u8 *)base);
    memcpy(entry, header, 0x80);
    final_offset = entry_index << 7;
    final_base = card_save_slot_metadata;
    final_entry = (s32 *)((u8 *)final_base + final_offset);
    final_entry[0] = 1;
}
