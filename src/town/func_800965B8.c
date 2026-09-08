#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80090A64;
extern M2C_UNK D_80093D48;
extern M2C_UNK *D_800FE5D8;

/* Initializes the output pointer and the shared data pointer. */
void func_80093D18(M2C_UNK **out_ptr) {
    *out_ptr = &D_80090A64;
    D_800FE5D8 = &D_80093D48;
}
