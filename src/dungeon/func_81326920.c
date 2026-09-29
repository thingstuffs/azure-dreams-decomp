#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


extern EntityRec *D_80174704;

/* Return whether the current record's unk_D2 field is zero. */
s32 func_8016E120(void) {
    return D_80174704->unk_D2 == 0;
}
