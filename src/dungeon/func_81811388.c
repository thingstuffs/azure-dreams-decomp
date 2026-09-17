#include "common.h"

extern s32 func_80049DE8(s32 target, s32 input_value, s32 count);
extern u8 D_800294F8[];

/* Return the selection updated by the indexed table's item count. */
s32 func_80026388(s32 input_value, s32 target, s32 lookup_index)
{
    return func_80049DE8(target, input_value, D_800294F8[lookup_index]);
}
