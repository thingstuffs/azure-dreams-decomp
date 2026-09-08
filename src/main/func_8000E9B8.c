#include "common.h"

typedef struct {
    s8 pad0[0x18];
    s32 field18;
    s8 pad1[0xC]; /* 0x28 total */
} EntryT;

extern EntryT D_80028570[];

/* Returns the blocks remaining after summing the entry sizes in 8192-byte units. */
s32 func_800219B8(s32 entry_count) {
    EntryT *entry;
    s32 total_size;
    s32 entry_index;
    s32 size_value;

    entry_index = 0;
    total_size = entry_index;
    size_value = (s32)&D_80028570[0];
    if (entry_count > 0) {
        entry = (EntryT *)size_value;
        do {
            size_value = entry->field18;
            entry_index += 1;
            total_size += size_value;
            entry += 1;
        } while (entry_index < entry_count);
    }
    size_value = total_size;
    if (total_size < 0) {
        size_value = total_size + 0x1FFF;
    }
    total_size = size_value >> 0xD;
    return 0xF - total_size;
}
