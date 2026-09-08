#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E4FC(); /* extern */
extern M2C_UNK D_800DF3E4;

/* Passes D_800DF3E4 to func_8003E4FC with selector 6 and a zero final argument. */
void func_800BD158(void) {
    func_8003E4FC(6, &D_800DF3E4, 0);
}
