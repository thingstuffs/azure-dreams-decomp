#include "common.h"

extern void func_8004DD2C(s32 context);
extern void SD_Call(s32 flags);
extern void townToggleSelectedEntryFlag(void *state);
extern void townStoreRecordCheckResult(void *record);
extern s32 townCheckEntryLimitOrCombinedValue(void *entry);
extern void close_twin_shop(void *shop);
extern void townProcessShopObjectData(s32 object_addr);

extern s32 D_800D1558;
extern s32 D_800D155C;

/* Handles the selected entry according to its type, flags, and availability. */
void townHandleSelectedEntry(s32 *state) {
    u8 *selected_entry;

    selected_entry = (u8 *) (state[1] * 4 + state[8]);
    if (selected_entry[1] != 0x16) {
        if (!(selected_entry[3] & 0x80)) {
            if (townCheckEntryLimitOrCombinedValue(state) != 0) {
                SD_Call(0x503);
                townToggleSelectedEntryFlag(state);
                townProcessShopObjectData(state[10]);
                return;
            }
            SD_Call(0x506);
            func_8004DD2C(D_800D1558);
            return;
        }
        SD_Call(0x506);
        if (state[6] == 1) {
            func_8004DD2C(D_800D155C);
            return;
        }
    } else {
        close_twin_shop((s8 *) state - 0x20);
        townStoreRecordCheckResult(state);
    }
}
