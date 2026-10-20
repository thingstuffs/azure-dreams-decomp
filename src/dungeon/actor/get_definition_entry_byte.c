#include "common.h"
#include "shared/def_table.h"


/* Returns the last byte of the selected 20-byte table entry. */
s32 get_definition_entry_byte_13(s16 entry_index) {
    DefEntry *entry = &D_8006DE24[entry_index];
    return entry->unk_13;
}
