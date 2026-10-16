/* Relink of matched town/func_8032FBA4; every changed retail word is a paired relocation. */
#define townMarkIndexedRecords8000 func_80017300
#include "common.h"

typedef struct {
    u32 flags;
    u8 pad[24];
} Struct8032FBA4Entry;

/* Set flag 0x8000 on each entry listed before the 0xFF terminator. */
void func_80017300(Struct8032FBA4Entry *entries, u8 *entry_indices) {
    u8 *index_cursor = entry_indices;

    if (*index_cursor != 0xFF) {
        do {
            entries[*index_cursor].flags |= 0x8000;
            index_cursor++;
        } while (*index_cursor != 0xFF);
    }
}
