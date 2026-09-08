#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80021538();                            /* extern */
extern s32 D_800287E4;

/* Returns the pending card status and processes it when nonzero. */
s32 func_800214FC(void) {
    s32 card_status;

    card_status = 0;
    if (D_800287E4 != 0) {
        card_status = D_800287E4;
        func_80021538();
    }
    return card_status;
}
