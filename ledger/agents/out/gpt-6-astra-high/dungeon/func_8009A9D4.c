#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_D_800E3D7C.h"

/* Returns the signed difference between the records' 16-bit values at offset 0x88. */
s16 func_800A0134(Rec_D_800814A8 *left_record, Rec_D_800E3D7C *right_record) {
    return (s16) (left_record->unk_88.as_u16 - right_record->unk_88.as_u16);
}
