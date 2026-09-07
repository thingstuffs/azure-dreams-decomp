#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80016000;

void func_806DB134(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 0xA;
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), M2C_UNK (**)(s8 *), 0x50)(sp10);
}
