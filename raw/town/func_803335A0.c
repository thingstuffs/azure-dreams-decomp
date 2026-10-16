#include "common.h"

extern u8 D_8001F2FC[];
extern u8 D_8001F360[];
extern s32 func_8001A51C(void *, void *);
s32 func_8001DDA0(void) { return func_8001A51C(D_8001F2FC, D_8001F360); }
