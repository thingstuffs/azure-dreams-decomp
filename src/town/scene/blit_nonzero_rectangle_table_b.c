#include "common.h"

extern u8 D_8001F2FC[];
extern u8 D_8001F360[];
extern s32 blit_nonzero_u16_rectangle(void *, void *);
/* Calls blit_nonzero_u16_rectangle with D_8001F2FC, D_8001F360 and returns its result. */
s32 blit_nonzero_rectangle_from_table_b(void) { return blit_nonzero_u16_rectangle(D_8001F2FC, D_8001F360); }
