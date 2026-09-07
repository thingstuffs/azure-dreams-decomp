#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80018854();
extern void *D_80016000;

void func_80017308(void) {
    func_80018854(0x514);
    M2C_FIELD(((M2C_FIELD(D_80016000, s32 *, 8) * 8) + M2C_FIELD(D_80016000, s32 *, 0x40)), s8 *, 2) = 2;
}
