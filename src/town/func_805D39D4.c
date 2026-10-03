#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns whether the stored value is below the threshold. */
s32 func_805D39D4(u32 threshold) {
    return (u32) D_80016000->unk_38->unk_2D5C < threshold;
}
