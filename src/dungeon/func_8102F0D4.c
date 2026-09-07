#include "common.h"
#include "records/Rec_D_80082E80.h"
typedef long long M2C_S64;

typedef struct S_8102F0D4_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F0D4_0;   /* arg1 in func_8102F0D4 */

typedef struct S_8102F0D4_1_pre {
    u16 unk_00;
} S_8102F0D4_1_pre;   /* the 0x2 bytes before arg0 in func_8102F0D4, addressed as arg0[-1] */

typedef struct S_8102F0D4_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_8102F0D4_1;   /* arg0 in func_8102F0D4 */

typedef struct S_8102F0D4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F0D4_2;   /* temp_v1 in func_8102F0D4 */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
s32 func_80065420();
extern s32 func_800478B8();

void func_8102F0D4(void *arg0, S_8102F0D4_0 *arg1, Rec_D_80082E80 *arg2) {
    u16 sp10[3];
    M2C_S64 sp18;
    s16 sp20;
    M2C_UNK sp24;
    s32 temp_v0;
    s32 temp_v1_2;
    s8 *temp_a1;
    u16 temp_v0_2;
    S_8102F0D4_2 *temp_v1;

    sp10[0] = arg1->unk_02;
    sp10[1] = arg1->unk_06;
    sp10[2] = arg1->unk_0A;
    temp_v0 = func_80065420(sp10, &sp18, &sp20, &sp24);
    temp_v1 = ((S_8102F0D4_1 *)arg0)->unk_A8;
    sp10[0] = temp_v1->unk_02;
    sp10[1] = temp_v1->unk_06;
    sp10[2] = temp_v1->unk_0A;
    temp_v1_2 = func_80065420(sp10, &sp18, &sp20, &sp24);
    temp_a1 = &D_800DCECC[((s32) (*D_80083228 + ((S_8102F0D4_1 *)arg0)->unk_94 + 0x100) >> 9) & 7];
    arg2->unk_06.as_s16 = (s16) ((temp_v0 - temp_v1_2) - (*temp_a1 * 2));
    func_800478B8(arg2, temp_a1);
    temp_v0_2 = ((S_8102F0D4_1 *)arg0)->unk_96 - 1;
    ((S_8102F0D4_1 *)arg0)->unk_96 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((S_8102F0D4_1_pre *)arg0)[-1].unk_00 = (u16) (((S_8102F0D4_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
