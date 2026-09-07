#include "common.h"
typedef s32 M2C_UNK;
typedef long long M2C_S64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
s32 func_80065420();
extern s32 func_800478B8();

void func_8102F0D4(void *arg0, void *arg1, void *arg2) {
    u16 sp10[3];
    M2C_S64 sp18;
    s16 sp20;
    M2C_UNK sp24;
    s32 temp_v0;
    s32 temp_v1_2;
    s8 *temp_a1;
    u16 temp_v0_2;
    void *temp_v1;

    sp10[0] = M2C_FIELD(arg1, u16 *, 2);
    sp10[1] = M2C_FIELD(arg1, u16 *, 6);
    sp10[2] = M2C_FIELD(arg1, u16 *, 0xA);
    temp_v0 = func_80065420(sp10, &sp18, &sp20, &sp24);
    temp_v1 = M2C_FIELD(arg0, void **, 0xA8);
    sp10[0] = M2C_FIELD(temp_v1, u16 *, 2);
    sp10[1] = M2C_FIELD(temp_v1, u16 *, 6);
    sp10[2] = M2C_FIELD(temp_v1, u16 *, 0xA);
    temp_v1_2 = func_80065420(sp10, &sp18, &sp20, &sp24);
    temp_a1 = &D_800DCECC[((s32) (*D_80083228 + M2C_FIELD(arg0, s16 *, 0x94) + 0x100) >> 9) & 7];
    M2C_FIELD(arg2, s16 *, 6) = (s16) ((temp_v0 - temp_v1_2) - (*temp_a1 * 2));
    func_800478B8(arg2, temp_a1);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
