#include "common.h"
#include "m2c_compat.h"

void process_all_lookup_entries();                      /* extern */
extern u8 D_800FC428;

/* Pass the entry index and its 64-byte record to process_all_lookup_entries. */
void process_indexed_entry_record(s32 entry_index) {
    process_all_lookup_entries(entry_index, (entry_index << 6) + &D_800FC428);
}
