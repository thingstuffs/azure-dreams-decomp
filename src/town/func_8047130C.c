#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 D_8001B210;


/* Check whether the stored value has reached the D_8001B210 threshold. */
s32 func_8047130C(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= (u32) D_8001B210;
}
