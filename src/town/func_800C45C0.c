#include "common.h"

extern s32 D_800D456C;
void func_800C1C68(s32, void *);

/* Passes the value and shared data address to func_800C1C68. */
void func_800C1D20(s32 value) {
    func_800C1C68(value, &D_800D456C);
}
