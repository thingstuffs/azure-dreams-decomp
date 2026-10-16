#include "common.h"

extern void townPassIndexedEntryAddress(void *entry_table);
extern void townHandleTwinShopInput(s32 *menu);
extern void townHandleGridMenuInput(s32 *menu);

/* Decrement the countdown and select the next dispatch when it expires. */
void func_800AE090(void *state_data) {
    u8 *state = (u8 *)state_data;
    void *handler;

    if (--*(s32 *)(state + 0x14) == 0) {
        if (*(s32 *)(state + 0x1C) != 0) {
            handler = townHandleTwinShopInput;
        } else {
            townPassIndexedEntryAddress(state);
            handler = townHandleGridMenuInput;
        }
        *(void **)(state - 0x10) = handler;
    }
}
