#include "common.h"

extern s32 func_80048E00(s32, s32*);
extern s32 func_800B0870(s32, s32*);
extern s32 D_800D15C4;

void func_800B08D4(s32 arg0) {
    func_80048E00(arg0, &D_800D15C4);
    func_800B0870(arg0 + 0x48, &D_800D15C4);
}
