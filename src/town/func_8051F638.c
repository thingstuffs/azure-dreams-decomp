#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Adds 0x20 to the linked record's unk_04 value. */
void func_80016E38(void) {
    TownPositionState *linked_record;

    linked_record = D_80016000->unk_1C;
    linked_record->x = (s32) (linked_record->x + 0x20);
}
