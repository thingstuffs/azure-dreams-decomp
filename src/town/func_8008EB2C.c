#include "common.h"
#include "m2c_compat.h"

void townProcessAllLookupEntries();                      /* extern */
extern u8 D_800FC428;

/* Pass the entry index and its 64-byte record to townProcessAllLookupEntries. */
void townProcessIndexedEntryRecord(s32 entry_index) {
    townProcessAllLookupEntries(entry_index, (entry_index << 6) + &D_800FC428);
}
