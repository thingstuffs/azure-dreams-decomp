#include "common.h"
#include "m2c_compat.h"

s32 func_8008AD1C(s32, M2C_UNK, M2C_UNK);                                /* extern */
M2C_UNK func_8008AE4C();                         /* extern */
s32 func_8008AFB0();      /* extern */

/* Find or allocate the matching entry and move it to the front. */
void func_8008B0E8(s32 kind, M2C_UNK state, M2C_UNK value) {
    s32 entry_index;

    entry_index = func_8008AD1C(kind, state, value);
    if (entry_index < 0) {
        entry_index = func_8008AFB0(kind, state, value, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        func_8008AE4C(entry_index);
    }
}
