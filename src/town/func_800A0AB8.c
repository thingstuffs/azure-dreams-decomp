#include "modules/town_town_windows.h"

/* Store the current record's signed value and table lookup in the script globals. */
s32 townStoreRecordValueAndTableLookup(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4->value;
    D_80082A38[0x13] = D_800D0910[D_800CFCC4->kind];
    return 0;
}
