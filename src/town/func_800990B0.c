#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_80096788(Rec_D_800E3D7C *);                                /* extern */
M2C_UNK func_800967E0();                 /* extern */
extern s32 D_800FE5D4;


/* Update the record to the computed upper bound when the global state permits. */
void func_80096810(Rec_D_800E3D7C *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (func_80096788(record) << 0x10) - 1;
        if (upper_bound >= record->unk_08.at00_s32.v) {
            func_800967E0(record, upper_bound);
        }
    }
}
