#include "common.h"
#include "m2c_compat.h"

M2C_UNK file_load_com();                   /* extern */
extern M2C_UNK D_800D1B64;

/* Pass D_800D1B64 to file_load_com. */
void func_800B9890(void) {
    file_load_com(&D_800D1B64);
}
