#include "common.h"

extern u8 D_8001F2DC[];
extern u8 D_8001F2F4[];
extern s32 func_8001A51C(void *, void *);
s32 func_8001DD74(void) { return func_8001A51C(D_8001F2DC, D_8001F2F4); }
