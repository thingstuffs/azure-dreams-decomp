#include "common.h"

s32 func_804019B4();                                /* extern */
s32 func_80401A50();                             /* extern */

extern s32 D_80136140[];
extern s32 D_8009EB58[];
extern s32 D_804094EC[];

/* Store the entry ID and its associated value in the selected slot. */
void func_8001B214(void) {
    s32 slot_index;
    s32 entry_id;

    slot_index = D_804094EC[0] != 0;
    entry_id = func_804019B4();
    D_80136140[slot_index] = entry_id;
    D_8009EB58[slot_index] = func_80401A50(entry_id);
}
