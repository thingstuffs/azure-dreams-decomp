#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

/* Returns whether the current record's unk_01 field is 2. */
s32 func_8001988C(void) {
    return D_8001E950->unk_01 == 2;
}
