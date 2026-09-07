#include "common.h"

typedef s32 M2C_UNK;

extern s32 D_80174AB4;
extern s16 D_80174AB8;
extern M2C_UNK D_80174BEC[];
extern void *D_80174CD8;

void func_80171130(s32 arg0) {
    D_80174AB8 = 0;
    D_80174AB4 = D_80174BEC[arg0];
    *(s16 *)((s8 *)D_80174CD8 + 0xD2) = 1;
}
