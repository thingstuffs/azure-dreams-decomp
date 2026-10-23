#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Subtracts an amount from the record's value at offset 0x2D5C. */
void subtract_money(s32 amount) {
    TownStateRecord *record;

    record = town_scene_root->town_state;
    record->money = (s32) (((signed int)record->money) - amount);
}
