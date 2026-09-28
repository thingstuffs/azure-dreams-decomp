#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"




/* Returns whether the global record's unk_104 field is zero. */
s32 func_800B14B4(void) {
    return ((Rec_D_800E3D7C *)D_800E3D7C)->unk_104 == 0;
}
