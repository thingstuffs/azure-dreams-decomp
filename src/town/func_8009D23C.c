#include "common.h"

extern void func_80035208(void *arg0);
extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_800988C8(void *arg0, s32 arg1, s32 arg2);
extern void func_80099754(s32 arg0);

extern u8 D_8006CADE[];
extern u8 D_800834B8[];
extern u8 D_800D0078[];

void func_8009A99C(s32 arg0)
{
    void *temp_s0;
    void *temp_v0;
    s32 temp_s2;
    s32 temp_s3;

    temp_s0 = D_800834B8;
    temp_v0 = (s8 *)temp_s0 - 0x20;
    temp_s3 = *(s32 *)((s8 *)temp_v0 + 8);
    temp_s2 = *(s32 *)((s8 *)temp_v0 + 0xC);
    func_80099754(temp_s3);
    *(s16 *)((s8 *)temp_s0 + 0x10) = arg0 & 0xFFF;
    func_80094984(D_800D0078, temp_s0, temp_s2);
    func_800988C8(temp_s0, temp_s3, temp_s2);
    func_80035208(D_8006CADE);
}
