#include "common.h"
#include "m2c_compat.h"
s32 lookup_entry_and_apply_record_code();
extern M2C_UNK D_80018E18;
/* Feed the value to the D_80018E18 record. */
void func_800169D0(s32 value)
{
    M2C_UNK *record;
    record = &D_80018E18;
    lookup_entry_and_apply_record_code(record, value);
}
