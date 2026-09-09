#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098ABC(void *, void *, s32);                            /* extern */
extern s8 D_80082668;

/* Clear D_80082668 and pass the state, context, and mode to func_80098ABC. */
void func_80098A98(void *state, void *context, s32 mode) {
    D_80082668 = 0;
    func_80098ABC(state, context, mode);
}
