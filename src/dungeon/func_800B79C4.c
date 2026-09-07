#include "common.h"

extern void func_8003E4FC(s32, void *, s32);
extern s8 D_800DCF4D;
extern s32 D_800DF3DC;

void func_800BD124(void) {
    func_8003E4FC(6, &D_800DF3DC, 0);
    D_800DCF4D = -1;
}
