#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Scale the linked record's value by 64 and add 0x220. */
void func_80016DE0(void) {
    TownPositionState *record;

    record = D_80016000->unk_1C;
    record->x = (s32) ((record->x << 6) + 0x220);
}
