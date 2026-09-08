#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB030_arg0.h"

s32 func_800644B8();                             /* extern */


s16 func_800AB030(Rec_func_800AB030_arg0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6A + 0xCC;
    arg0->unk_6A = temp_v0;
    return (s16) (func_800644B8((s16) temp_v0) / 384);
}
