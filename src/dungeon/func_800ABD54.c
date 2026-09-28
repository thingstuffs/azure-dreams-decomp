#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"




/* Returns whether the global record's unk_104 field is zero. */
s32 func_800B14B4(void) {
    return D_800E3D7C->unk_104 == 0;
}
