#include "common.h"
#include "m2c_compat.h"

void func_8009CEE8();                            /* extern */
void func_800A496C();                            /* extern */

/* Runs func_8009CEE8 followed by func_800A496C. */
void func_8009CE80(void) {
    func_8009CEE8();
    func_800A496C();
}
