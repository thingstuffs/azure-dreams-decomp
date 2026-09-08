#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003AF58();        /* extern */
extern M2C_UNK D_8006AE64;
extern M2C_UNK D_800717D0;

/* Passes D_8006AE64 and the shared D_800717D0 context to func_8003AF58. */
void func_8003B298(void) {
    func_8003AF58(&D_800717D0, &D_8006AE64);
}
