#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *D_80016000;

void func_80480208(void) {
    FIELD(FIELD(D_80016000, void **, 0x1C), s32 *, 0) = 1;
    FIELD(FIELD(D_80016000, void **, 0x1C), s32 *, 4) = 11;
    FIELD(FIELD(D_80016000, void **, 0x1C), s32 *, 8) = 3;
}
