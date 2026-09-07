#include "common.h"

/* Struct pointed to by the entity's "parent"/owner pointer, which sits 0x14
 * bytes before the entity struct itself. Only the field at offset 0x12
 * (a bitfield-ish u16 status word) is touched here. */
typedef struct S_80042984 {
    u8 pad_0x00[0x12];
    u16 field_0x12;
} S_80042984;

extern s32 func_800429E4(void *a0);

/* If the entity's type/id byte (offset 0x13) is in [3, 45], recompute a
 * status word on the owning object: keep the low 6 bits masked off and
 * OR/add in 4 * func_800429E4(a0). */
void func_80042984(void *a0)
{
    u8 v0 = ((u8 *)a0)[0x13];

    if ((u32)(v0 - 3) < 0x2B) {
        S_80042984 *s0 = *(S_80042984 **)((u8 *)a0 - 0x14);
        s32 v1 = s0->field_0x12 & 0xFFC0;

        s0->field_0x12 = v1 + (func_800429E4(a0) << 2);
    }
}
