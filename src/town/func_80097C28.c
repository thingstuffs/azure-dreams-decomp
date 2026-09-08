#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


/* Add 0x20000 to the record's signed value at offset 0x14. */
void func_80095388(Rec_D_800E3D7C *record) {
    record->unk_14.as_s32 = (s32) (record->unk_14.as_s32 + 0x20000);
}
