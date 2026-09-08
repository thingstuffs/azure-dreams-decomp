#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F2D4(s32, M2C_UNK);                            /* extern */
M2C_UNK func_8008F350();                /* extern */

/* Pass the same value and context to both processing routines. */
void func_8008F294(s32 value, M2C_UNK context) {
    func_8008F2D4(value, context);
    func_8008F350(value, context);
}
