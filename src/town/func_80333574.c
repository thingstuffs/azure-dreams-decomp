#include "common.h"

extern u8 D_8001F2DC[];
extern u8 D_8001F2F4[];
extern s32 townBlitNonzeroU16Rectangle(void *, void *);
s32 func_8001DD74(void) { return townBlitNonzeroU16Rectangle(D_8001F2DC, D_8001F2F4); }
