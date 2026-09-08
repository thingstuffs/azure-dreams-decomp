#include "common.h"

extern s32 func_800B2918(void);

/* Return the computed value for mode 1 or 0x14 for other modes. */
s32 func_800B2130(s32 mode) {
    if (mode != 1) {
        return 0x14;
    }
    return func_800B2918();
}
