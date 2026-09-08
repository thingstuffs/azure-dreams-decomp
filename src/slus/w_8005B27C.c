#include "common.h"

typedef struct {
    s16 field_0;
    char pad4[6];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 D_80086C00[8];

extern void func_800564A8(s16 a0);

/* Stores two 7-bit values in the selected entry, then calls func_800564A8 for it. */
void func_8005B27C(s16 index, s32 value_8, s32 value_a)
{
    S_80086C00 *entries = D_80086C00;
    S_80086C00 *entry = entries + index;
    entry->field_8 = value_8 & 0x7F;
    entry->field_A = value_a & 0x7F;
    func_800564A8(index);
}
