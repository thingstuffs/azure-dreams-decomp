#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Subtracts an amount from the record's value at offset 0x2D5C. */
void func_8059E700(s32 amount) {
    TownStateRecord *record;

    record = D_80016000->unk_38;
    record->unk_2D5C = (s32) (((signed int)record->unk_2D5C) - amount);
}
