#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80174CD8.h"



extern Rec_D_80174CD8 *D_80174CD8;

/* Returns whether the current record's unk_D2 field is zero. */
s32 func_80171470(void) {
    return D_80174CD8->unk_D2 == 0;
}
