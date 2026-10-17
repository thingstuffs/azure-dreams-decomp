#include "common.h"
#include "m2c_compat.h"

void cardBootRefreshSlotWindow();                         /* extern */

typedef struct S_80026270_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80026270_0;

/* Runs cardBootRefreshSlotWindow on each of five stored object addresses. */
void cardBootRefreshFiveSlotObjects(void *object_list) {
    s32 object_addr;
    s32 object_index;
    void *entry_cursor;

    object_index = 0;
    entry_cursor = object_list;
    do {
        object_addr = ((S_80026270_0 *)entry_cursor)->unk_0C;
        entry_cursor += 4;
        object_index += 1;
        cardBootRefreshSlotWindow(object_addr);
    } while (object_index < 5);
}
