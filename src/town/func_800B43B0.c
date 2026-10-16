#include "common.h"

void townInitializeTemplatedStateAndPosition(s32, s32, s32, s32, s32); /* extern */
void townInitializePanelContentAndPositions(s32); /* extern */
void townStorePairValues(s32, s32); /* extern */

/* Set up the object, update its embedded records, and finalize it. */
void func_800B1B10(s32 object_addr, s32 setup_value, s32 update_value_1, s32 update_value_2) {
    townStorePairValues(object_addr, setup_value);
    townInitializeTemplatedStateAndPosition(object_addr + 0x38, object_addr + 0x10, object_addr + 0x20, update_value_1, update_value_2);
    townInitializePanelContentAndPositions(object_addr);
}
