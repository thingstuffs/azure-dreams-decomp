#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns whether the referenced record's signed value at offset 0x35BE is at least 51. */
s32 func_8050E188(void) {
    return D_80016000->unk_38->unk_35BE >= 0x33;
}
