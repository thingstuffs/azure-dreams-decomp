#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 D_80018340;


/* Checks whether the stored value has reached the threshold in D_80018340. */
s32 func_8065C3FC(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= (u32) D_80018340;
}
