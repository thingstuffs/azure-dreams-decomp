#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


/* Clears the record's three fields at offsets 0x0C through 0x14. */
void func_80099754(Rec_D_800E3D7C *record) {
    record->unk_0C.as_s32 = 0;
    record->unk_10.at00_s32.v = 0;
    record->unk_14.as_s32 = 0;
}
