/* Relink of matched town/func_8032C364; every changed retail word is a paired relocation. */
#define townCallStateRefreshAndReturnZero func_80016EC0
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001DDA0();                            /* extern */

/* Calls func_8001DDA0 and returns zero. */
s32 func_80016EC0(void) {
    func_8001DDA0();
    return 0;
}
