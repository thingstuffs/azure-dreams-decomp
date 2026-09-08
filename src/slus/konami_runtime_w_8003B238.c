#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003AF58();        /* extern */
extern M2C_UNK D_8006AE4C;
extern M2C_UNK D_800717D0;

/* Passes D_8006AE4C and the shared D_800717D0 context to func_8003AF58. */
void func_8003B238(void) {
    func_8003AF58(&D_800717D0, &D_8006AE4C);
}
