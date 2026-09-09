#include "common.h"
#include "m2c_compat.h"

M2C_UNK Control_CD(); /* extern */
extern M2C_UNK D_800DF3E4;

/* Passes D_800DF3E4 to Control_CD with selector 6 and a zero final argument. */
void func_800BD158(void) {
    Control_CD(6, &D_800DF3E4, 0);
}
