#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_80099754(void *arg0);
extern M2C_UNK D_8009AFF4[3];
extern M2C_UNK D_800D0078[3];
extern s32 D_800D0620;
extern M2C_UNK D_800D0640[3];

void func_8009B014(void *arg0, void *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    s32 temp_index;
    s32 *temp_base;
    s32 *temp_a2;

    temp_index = D_800D0620;
    temp_base = D_800D0640;
    temp_a2 = temp_base + temp_index;
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((u32) (M2C_FIELD(arg0, s16 *, 0x32) * 0x10000) + (u32) *temp_a2 - (u32) M2C_FIELD(arg1, s32 *, 4)) / M2C_FIELD(arg0, s16 *, 0xA);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0;
    if (((s16) temp_v0 * 0x10000) <= 0) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) ((u32) (M2C_FIELD(arg0, s16 *, 0x32) * 0x10000) + (u32) *temp_a2);
        func_80099754(arg1);
        M2C_FIELD(arg0, s16 *, 0x10) = 0x400;
        M2C_FIELD(arg0, u16 *, 0xA) = 0xA;
        func_80094984(D_800D0078, arg0, arg2);
        M2C_FIELD(arg0, M2C_UNK **, 4) = D_8009AFF4;
    }
}
