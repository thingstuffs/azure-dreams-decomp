#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"




/* Return whether the current record's unk_9A value differs from 0x29. */
s32 func_800B14DC(void) {
    return ((EntityRec *)D_800E3D7C)->unk_9A != 0x29;
}
