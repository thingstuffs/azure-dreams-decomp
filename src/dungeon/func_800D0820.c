#include "common.h"
#include "m2c_compat.h"

extern s8 D_800E2468[];
s32 func_800A45D8(s32, s32, s16);
s16 func_800BCB04(s32, s32, s16);

typedef struct S_800D5F80_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D5F80_0;   /* arg0 in func_800D5F80 */

typedef struct S_800D5F80_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800D5F80_1;   /* arg1 in func_800D5F80 */

typedef struct S_800D5F80_2 {
    s16 unk_00;
    s16 unk_02;
} S_800D5F80_2;   /* temp_a1 in func_800D5F80 */

s32 func_800D5F80(S_800D5F80_0 *arg0, S_800D5F80_1 *arg1) {
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_s1;
    s16 temp_height;
    s32 temp_raw_height;
    void *temp_table;
    S_800D5F80_2 *temp_a1;

    temp_raw_height = arg0->unk_0A;
    temp_height = temp_raw_height - 0x20;
    temp_table = D_800E2468;
    temp_a1 = temp_table + ((arg1->unk_2A >> 7) & 0x1C);
    temp_s1 = (arg0->unk_02 + (temp_a1->unk_00 << 6)) & 0xFFFF;
    temp_s0 = (arg0->unk_06 + (temp_a1->unk_02 << 6)) & 0xFFFF;
    if ((func_800A45D8(temp_s1, temp_s0, temp_height) << 0x10) == 0) {
        temp_v0_2 = func_800BCB04(temp_s1, temp_s0, temp_height);
        if (temp_v0_2 < 0x200 &&
            (arg0->unk_0A - 0x40) < temp_v0_2) {
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}
