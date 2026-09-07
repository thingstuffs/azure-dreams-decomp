#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80016000[];

void func_8001AEC8(void) {
    ASM_SCHED_BARRIER();
    M2C_FIELD(M2C_FIELD(D_80016000[0], void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x30C)(0x9000);
}
