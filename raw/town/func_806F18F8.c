#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;

void func_806F18F8(void) {
    s32 record[6];
    void *state;

    state = M2C_FIELD(&D_80016000, void **, 0);
    record[0] = M2C_FIELD(M2C_FIELD(state, volatile void **, 0x1C), s32 *, 4);
    record[1] = M2C_FIELD(M2C_FIELD(state, volatile void **, 0x1C), s32 *, 4);
    record[2] = 0;
    M2C_FIELD(M2C_FIELD(state, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x208)(0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(s32 *), 0x228)(record);
}

/* MECHANISM: The six-word sibling array forces the 0x30 frame; s0 holds D_80016000's high page.
   Reloading the bottom state from &D_80016000 itself avoids the seed's stray full-address addiu.
   That preserves the load-delay nop and places move a0,zero in the first jalr delay slot. */
