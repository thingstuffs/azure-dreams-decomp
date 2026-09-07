#include "common.h"

typedef struct S_800DC724_0 {
    u8 pad_00[0x3C];
    void * unk_3C;
    u8 pad_40[0x10];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} S_800DC724_0;   /* arg0 in func_800DC724 */

typedef struct S_800DC724_1 {
    u16 unk_00;
    u16 unk_02;
} S_800DC724_1;   /* temp_v0 in func_800DC724 */

typedef struct S_800DC724_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800DC724_2;   /* holder in func_800DC724 */

typedef struct S_800DC724_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800DC724_3;   /* temp_a0 in func_800DC724 */



extern s32 func_80053DA8();
extern s32 func_800DC650();
extern u8 D_800E2924[];

void func_800DC724(S_800DC724_0 *arg0, s32 arg1)
{
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 temp_a2;
    s32 index;
    s32 target_x;
    u8 *table;
    S_800DC724_2 *holder;
    S_800DC724_3 *temp_a0;
    S_800DC724_1 *temp_v0;

    table = D_800E2924;
    index = arg0->unk_50;
    holder = arg0->unk_3C;
    temp_v0 = (index * 4) + table;
    target_x = temp_v0->unk_00;
    do { temp_a2 = temp_v0->unk_02; } while (0);
    do { temp_a0 = holder->unk_04; } while (0);
    arg0->unk_58 = 0;
    temp_v1 = (s16)target_x - temp_a0->unk_08;
    if (temp_v1 != 0) {
        do { arg0->unk_58 = 1; } while (0);
        arg1 = temp_a0->unk_08;
        var_v0 = temp_v1 + 3;
        if (temp_v1 <= 0) {
            var_v0 = temp_v1 - 3;
        }
        temp_a0->unk_08 = arg1 + (var_v0 >> 2);
    }
    temp_v1_2 = (s16)temp_a2 - temp_a0->unk_0A;
    if (temp_v1_2 != 0) {
        arg0->unk_58 = 1;
        arg1 = temp_a0->unk_0A;
        var_v0_2 = temp_v1_2 + 3;
        if (temp_v1_2 <= 0) {
            var_v0_2 = temp_v1_2 - 3;
        }
        temp_a0->unk_0A = arg1 + (var_v0_2 >> 2);
    }
    func_800DC650(arg0, arg1, temp_a2);
    if (arg0->unk_58 != 0) {
        return;
    }
    temp_v1_3 = arg0->unk_50;
    temp_v0_2 = arg0->unk_54;
    if (temp_v1_3 == temp_v0_2) {
        return;
    }
    if ((temp_v0_2 ^ temp_v1_3) & 2) {
        func_80053DA8(0x507);
    }
    arg0->unk_50 = arg0->unk_54;
}
