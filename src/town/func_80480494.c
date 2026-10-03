#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 D_80019438;


/* Check whether the record value meets the threshold in D_80019438. */
s32 func_80480494(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= (u32) D_80019438;
}
