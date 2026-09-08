#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"

s32 func_8008FE90(Rec_D_800FE490 *);                                /* extern */


/* Updates the record's unk_10 value using func_8008FE90. */
void func_80095910(Rec_D_800FE490 *record) {
    record->unk_10 = func_8008FE90(record);
}
