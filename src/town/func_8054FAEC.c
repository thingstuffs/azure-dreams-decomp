#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns whether the current record's value at offset 0x2D5C is at least 100. */
s32 func_8054FAEC(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= 0x64U;
}
