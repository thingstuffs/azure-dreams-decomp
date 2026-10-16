#include "common.h"

extern s32 townReadMapCellAtTile(s16 tile_x, s16 tile_y);
extern s32 townPassValueAndRangeGroups(s32 value);
extern void townWriteWrappedPackedNibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data);

/* Converts and processes all 128 entries for the given lookup key. */
void townProcessAllLookupEntries(s16 lookup_key, void *context) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 0x80; entry_index++) {
        townWriteWrappedPackedNibble(townPassValueAndRangeGroups(townReadMapCellAtTile(entry_index, lookup_key) & 0xFFFF), entry_index, 0x80, context);
    }
}
