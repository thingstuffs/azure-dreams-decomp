#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804014E4();                            /* extern */

/* Clears the value at 0x804094E8 and calls func_804014E4. */
void func_80019998(void) {
    *(s32 *)0x804094E8 = 0;
    func_804014E4();
}
