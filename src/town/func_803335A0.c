#include "common.h"

extern u8 D_8001F2FC[];
extern u8 D_8001F360[];
extern s32 townBlitNonzeroU16Rectangle(void *, void *);
s32 func_8001DDA0(void) { return townBlitNonzeroU16Rectangle(D_8001F2FC, D_8001F360); }
