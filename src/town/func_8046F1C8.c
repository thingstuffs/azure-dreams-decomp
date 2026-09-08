#include "common.h"

extern u8 D_8001A92C;
extern s32 func_8001A7B0(u8);

/* Check whether any entry in the zero-terminated list passes the predicate. */
s32 func_8046F1C8(void) {
    u8 *entry = &D_8001A92C;

    if (D_8001A92C != 0) {
        do {
            if (func_8001A7B0(*entry) != 0) {
                return 1;
            }
            entry++;
        } while (*entry != 0);
    }
    return 0;
}
