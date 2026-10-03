#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 D_80019B00;


/* Check whether the stored value meets the D_80019B00 threshold. */
s32 func_805D3984(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= (u32) D_80019B00;
}
