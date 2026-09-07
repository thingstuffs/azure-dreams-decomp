#include "common.h"

extern s32 func_800B7428(s16, s16, s32);
extern s32 D_800D17D8[];

void func_800B7934(s16 arg0, s16 arg1, u8 arg2) {
    func_800B7428(arg0, arg1, D_800D17D8[arg2]);
}
