#include "common.h"
#include "m2c_compat.h"

extern s32 D_80090A6C;

/* Sets the output pointer to D_80090A6C. */
void func_80093D38(M2C_UNK **out_ptr) {
    *out_ptr = &D_80090A6C;
}
