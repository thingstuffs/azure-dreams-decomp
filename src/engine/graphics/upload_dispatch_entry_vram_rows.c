#include "common.h"
#include "engine/graphics.h"

/* Linked-entry struct used by the D_8006CE80 table: each 0xC-byte slot
 * holds an unrelated value, a "next"-style pointer to another entry of
 * the same layout, and a trailing value. */
typedef struct S_8006CE80 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ struct S_8006CE80 *unk4;
    /* 0x8 */ s32 unk8;
} S_8006CE80;

extern S_8006CE80 dispatch_resource_records[];

/* Follow two links from the indexed entry and dispatch the final entry if both links exist. */
void upload_dispatch_entry_vram_rows(u16 entry_index) {
    S_8006CE80 *entry = &dispatch_resource_records[(u16)entry_index & 0xFFFF];
    S_8006CE80 *linked_entry = entry->unk4;

    if (linked_entry != 0) {
        linked_entry = linked_entry->unk4;
        if (linked_entry != 0) {
            upload_vram_entry_array(linked_entry);
        }
    }
}
