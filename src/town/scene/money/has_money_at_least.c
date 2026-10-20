#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Check whether the stored value meets the minimum. */
s32 has_money_at_least(u32 minimum) {
    return (u32) D_80016000->unk_38->unk_2D5C >= minimum;
}
