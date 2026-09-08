#include "common.h"
#include "m2c_compat.h"

extern u8 D_800D4258[];

typedef struct S_800C1770_0 {
    s16 unk_00;
} S_800C1770_0;   /* D_800D4258 in func_800C1770 */

typedef struct S_800C1770_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_800C1770_1;   /* temp_v0 in func_800C1770 */

/* Store four signed 16-bit values in D_800D4258. */
void func_800C1770(s16 value_0, s16 value_1, s16 value_2, s16 value_3) {
    u8 *values;

    ((S_800C1770_0 *)D_800D4258)->unk_00 = value_0;
    values = D_800D4258;
    ((S_800C1770_1 *)values)->unk_02 = value_1;
    ((S_800C1770_1 *)values)->unk_04 = value_2;
    ((S_800C1770_1 *)values)->unk_06 = value_3;
}
