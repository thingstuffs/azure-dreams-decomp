#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80026CF0_arg0.h"

extern M2C_UNK D_800789B8;


/* Store the default data pointer and supplied value through the record's pointers. */
void func_80026CF0(Rec_func_80026CF0_arg0 *record, s32 value) {
    *record->unk_0C = &D_800789B8;
    *record->unk_10 = value;
}
