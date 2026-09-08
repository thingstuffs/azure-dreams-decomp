#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800161B4();                            /* extern */
extern s32 D_8001967C;
extern s32 D_80019AFC;

/* Set state 4 and run the transition handler when the mode is 2. */
void func_805D213C(void) {
    if (D_80019AFC == 2) {
        D_8001967C = 4;
        func_800161B4();
    }
}
