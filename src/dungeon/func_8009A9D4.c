#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"
#include "shared/entity.h"

/* Returns the signed difference between the records' 16-bit values at offset 0x88. */
s16 func_800A0134(EntityRec *left_record, EntityRec *right_record) {
    return (s16) (((u16)left_record->unk_88) - ((u16)right_record->unk_88));
}
