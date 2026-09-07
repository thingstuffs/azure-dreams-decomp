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

void func_800C1770(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u8 *temp_v0;

    ((S_800C1770_0 *)D_800D4258)->unk_00 = arg0;
    temp_v0 = D_800D4258;
    ((S_800C1770_1 *)temp_v0)->unk_02 = arg1;
    ((S_800C1770_1 *)temp_v0)->unk_04 = arg2;
    ((S_800C1770_1 *)temp_v0)->unk_06 = arg3;
}
