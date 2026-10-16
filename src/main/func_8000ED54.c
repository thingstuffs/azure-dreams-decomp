#include "modules/main_server_ship.h"
#include "common.h"





/* Looks up a slot's record and processes it when present. */
s32 cardBootLoadSlotMetadata(s32 slot) {
    s32 record_data[8];
    s32 *source_id;
    u8 *state_base;
    s32 *slot_state;
    s32 lookup_result;
    s32 result;

    result = 1;
    cardBootBuildSlotPath(record_data, slot);
    source_id = &D_80084128[0];
    if ((*(s32 *)(&D_800287CC)) != 0) {
        source_id = &D_80084128[1];
    }
    lookup_result = cardBootHasDirectoryNamePrefix(*source_id, (u8 *)record_data + 5);
    state_base = (u8 *)(*(s32 (*)[])(&D_80083E98));
    slot_state = (s32 *)(state_base + (slot << 7));
    *slot_state = lookup_result;
    if (lookup_result != 0) {
        result = cardBootReadFileUnits128(record_data, slot_state, 1, 4);
        *slot_state = 1;
    }
    return result;
}
