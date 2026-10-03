#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



u32 func_80016134(s32, s32);                                /* extern */


/* Check whether the stored value meets the queried threshold. */
s32 func_806DB17C(s32 query_input, s32 query_param) {
    return (u32) D_80016000->unk_38->unk_2D5C >= func_80016134(query_input, query_param);
}
