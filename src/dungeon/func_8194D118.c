#include "common.h"

typedef struct S_80024918_0 {
    void * unk_00;
    u8 pad_04[0x30];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x28];
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
} S_80024918_0;   /* arg0 in func_80024918 */

typedef struct S_80024918_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80024918_1;   /* temp_v1 in func_80024918 */



extern s32 func_80024700();
extern u32 func_800644B8();
extern s32 D_800814A0;

void func_80024918(void *arg0) {
    s16 temp_v0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_y;
    void *temp_v1;

    temp_v1 = ((S_80024918_0 *)arg0)->unk_00;
    ((S_80024918_1 *)temp_v1)->unk_1A = ((S_80024918_1 *)temp_v1)->unk_1A + 1;
    ((S_80024918_0 *)arg0)->unk_78 = func_800644B8(((S_80024918_0 *)arg0)->unk_74 << 8) >> 6;
    temp_a1 = ((S_80024918_0 *)arg0)->unk_44;
    ((S_80024918_0 *)arg0)->unk_34 += ((S_80024918_0 *)arg0)->unk_40;
    temp_y = ((S_80024918_0 *)arg0)->unk_38;
    temp_a2 = ((S_80024918_0 *)arg0)->unk_48;
    ((S_80024918_0 *)arg0)->unk_38 = temp_y + temp_a1;
    ((S_80024918_0 *)arg0)->unk_3C += temp_a2;
    func_80024700(arg0, temp_a1, temp_a2);
    temp_v0 = (s16)((S_80024918_0 *)arg0)->unk_74 + 1;
    ((S_80024918_0 *)arg0)->unk_74 = temp_v0;
    if (temp_v0 >= 9) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
