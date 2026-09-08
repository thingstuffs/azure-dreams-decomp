#include "common.h"
#include "m2c_compat.h"

extern u8 D_800D4258[];

typedef struct S_800C17A0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800C17A0_0;   /* base in func_800C17A0 */

/* Stores the two field values in D_800D4258. */
void func_800C17A0(s16 value_04, s16 value_06) {
    u8 *base;

    base = D_800D4258;
    ((S_800C17A0_0 *)base)->unk_04 = value_04;
    ((S_800C17A0_0 *)base)->unk_06 = value_06;
}
