#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns the signed 16-bit value at offset 0x35BC in the referenced record. */
s16 func_80500158(void) {
    return D_80016000->unk_38->unk_35BC;
}
