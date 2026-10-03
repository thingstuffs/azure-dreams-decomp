#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

/* Return whether the stored value has reached 10000. */
s32 func_8001C778(void) {
    return (u32) D_80016000->unk_38->unk_2D68 >= 0x2710U;
}
