#include "common.h"

extern u8 D_8001F2DC[];
extern u8 D_8001F2F4[];
extern s32 blit_nonzero_u16_rectangle(void *, void *);
s32 blit_default_rectangle(void) { return blit_nonzero_u16_rectangle(D_8001F2DC, D_8001F2F4); }
