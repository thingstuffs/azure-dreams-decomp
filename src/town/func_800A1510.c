#include "common.h"

extern s32 func_8009FF8C(s32 arg0, void *arg1);
extern void func_800A00E8(s32 arg0);
extern s32 func_800B28A0(void);
extern s32 D_8009ED7C;
extern u8 D_80100B3B;

void func_8009EC70(void *arg0, void *arg1, void *arg2) {
    s32 result;
    *((s8 *)arg1 + 0x15) = 0;
    *(s32 *)((u8 *)arg2 + 0xC) = 0;
    *(s32 *)((u8 *)arg2 + 0x10) = 0;
    *(s32 *)((u8 *)arg2 + 0x14) = 0;
    *(s32 **)((u8 *)arg0 + 0x50) = &D_8009ED7C;
    *(s16 *)((u8 *)arg0 + 0x6C) = 0xA;
    if (*((u8 *)arg0 + 0x4D) == 0x13) {
        result = D_80100B3B;
    } else {
        result = func_8009FF8C(func_800B28A0(), arg2);
    }
    func_800A00E8(result);
}
