#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_80096788(Rec_D_800E3D7C *);                                /* extern */
M2C_UNK func_800967E0();                 /* extern */
extern s32 D_800FE5D4;


/* Applies the computed limit when it meets the record's threshold and the global state is negative. */
void func_80096810(Rec_D_800E3D7C *record) {
    s32 limit;

    if (D_800FE5D4 < 0) {
        limit = (func_80096788(record) << 0x10) - 1;
        if (limit >= record->unk_08.at00_s32.v) {
            func_800967E0(record, limit);
        }
    }
}
