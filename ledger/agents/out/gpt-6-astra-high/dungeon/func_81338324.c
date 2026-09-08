#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D50.h"



extern Rec_D_80175D50 *D_80175D50;

/* Checks whether the record's unk_BA field equals the expected value. */
s32 func_8016F324(s32 expected_value) {
    return D_80175D50->unk_BA == expected_value;
}
