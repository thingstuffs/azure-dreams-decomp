#include "common.h"

typedef s32 M2C_UNK;


extern M2C_UNK func_800A4B94();
extern M2C_UNK func_800A4CD8();
extern M2C_UNK D_800A4B94;


typedef struct S_800A4C10_0 {
    void * unk_00;
    void * unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    M2C_UNK * unk_28;
} S_800A4C10_0;   /* arg0 in func_800A4C10 */

typedef struct S_800A4C10_1 {
    s32 unk_00;
} S_800A4C10_1;   /* temp_v1 in func_800A4C10 */

typedef struct S_800A4C10_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800A4C10_2;   /* ((S_800A4C10_0 *)arg0)->unk_00 in func_800A4C10 */

void func_800A4C10(S_800A4C10_0 *arg0) {
    s32 temp_v0;
    S_800A4C10_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    if (temp_v1 != arg0->unk_04) {
        arg0->unk_20 = 9;
        arg0->unk_14 = 0;
        arg0->unk_18 = 0;
        arg0->unk_1C = 0;
        arg0->unk_04 = temp_v1;
        func_800A4B94(arg0);
        func_800A4CD8();
        return;
    }
    arg0->unk_08 +=
        (temp_v1->unk_00 - arg0->unk_08) /
        arg0->unk_20;
    arg0->unk_0C +=
        (((S_800A4C10_2 *)(arg0->unk_00))->unk_04 - arg0->unk_0C) /
        arg0->unk_20;
    arg0->unk_10 +=
        (((S_800A4C10_2 *)(arg0->unk_00))->unk_08 - arg0->unk_10) /
        arg0->unk_20;
    temp_v0 = arg0->unk_20 - 1;
    arg0->unk_20 = temp_v0;
    if (temp_v0 <= 0) {
        arg0->unk_28 = &D_800A4B94;
    }
}
