#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80016000;

void func_80016F40(void) {
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x1C), s32 *, 4) = 0x560;
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x1C), s32 *, 8) = 0x3E0;
}
