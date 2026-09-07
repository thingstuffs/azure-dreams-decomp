#include "common.h"

typedef struct {
    s16 field_0;
    char pad4[6];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 D_80086C00[8];

extern void func_800564A8(s16 a0);

/* Stores masked a1/a2 into the field_8/field_A of the D_80086C00 entry
   selected by index a0, then calls func_800564A8 with that same index. */
void func_8005B27C(s16 a0, s32 a1, s32 a2)
{
    S_80086C00 *base = D_80086C00;
    S_80086C00 *v0 = base + a0;
    v0->field_8 = a1 & 0x7F;
    v0->field_A = a2 & 0x7F;
    func_800564A8(a0);
}
