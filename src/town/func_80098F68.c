#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800954C4(Rec_D_800E3D7C *);                            /* extern */
extern s8 D_800CFCEB;


/* Set D_800CFCEB, initialize the record, and call func_800954C4. */
void func_800966C8(Rec_D_800E3D7C *record, s32 initial_value) {
    D_800CFCEB = 1;
    record->unk_00.at00_s32.v = initial_value;
    record->unk_0C.as_s32 = 0;
    func_800954C4(record);
}
