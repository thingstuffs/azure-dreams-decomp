#include "modules/main_server_ship.h"
#include "common.h"




/* Marks quest data as loaded, optionally refreshing its indexed entry while preserving its state. */
void cardBootLoadSaveAndClearMarker(s32 entry_index, void *data, s32 update_entry) {
    s32 context[8];
    s32 *entry_table;
    s32 *entry;
    s32 saved_state;

    cardBootBuildSlotPath(context, entry_index);
    if (cardBootReadFileUnits128(context, data, 0xC0, 0) == 0) {
        return;
    }
    if (cardBootVerifySaveXorChecksum(data) == 0) {
        return;
    }
    if (update_entry != 0) {
        saved_state = *(s16 *)((u8 *)data + 0x208);
        *(s16 *)((u8 *)data + 0x208) = 0;
        *(s32 *)((u8 *)data + 0x204) = 0;
        cardBootStoreSaveXorChecksum(data);
        entry_table = (s32 *)&(*(s32 (*)[][32])(&D_80083E98));
        entry = (s32 *)((u8 *)entry_table + (entry_index << 7));
        *(s16 *)((u8 *)entry + 8) = 0;
        *(s32 *)((u8 *)entry + 4) = *(s32 *)((u8 *)data + 0x204);
        cardBootWriteFileUnits128(context, entry, 1, 4, entry[0]);
        cardBootWriteFileUnits128(context, data, 1, 0, entry[0]);
        *(s16 *)((u8 *)data + 0x208) = saved_state;
        return;
    }
    *(s16 *)((u8 *)data + 0x208) = 0;
}
