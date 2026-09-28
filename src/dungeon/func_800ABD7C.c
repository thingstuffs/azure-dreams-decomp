#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"




/* Return whether the current record's unk_9A value differs from 0x29. */
s32 func_800B14DC(void) {
    return ((Rec_D_800E3D7C *)D_800E3D7C)->unk_9A != 0x29;
}
