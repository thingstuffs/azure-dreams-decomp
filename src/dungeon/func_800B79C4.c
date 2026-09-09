#include "common.h"

extern void Control_CD(s32, void *, s32);
extern s8 D_800DCF4D;
extern s32 D_800DF3DC;

/* Submit D_800DF3DC and reset D_800DCF4D to -1. */
void func_800BD124(void) {
    Control_CD(6, &D_800DF3DC, 0);
    D_800DCF4D = -1;
}
