#include "common.h"
#include "m2c_compat.h"

extern u8 D_800D4258[];

typedef struct S_800C17A0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800C17A0_0;   /* base in func_800C17A0 */

void func_800C17A0(s16 arg0, s16 arg1) {
    u8 *base;

    base = D_800D4258;
    ((S_800C17A0_0 *)base)->unk_04 = arg0;
    ((S_800C17A0_0 *)base)->unk_06 = arg1;
}
