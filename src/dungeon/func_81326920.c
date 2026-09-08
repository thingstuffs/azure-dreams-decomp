#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"



extern Rec_D_800E3D7C *D_80174704;

/* Return whether the current record's unk_D2 field is zero. */
s32 func_8016E120(void) {
    return D_80174704->unk_D2 == 0;
}
