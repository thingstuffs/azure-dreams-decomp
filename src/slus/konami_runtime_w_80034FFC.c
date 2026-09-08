#include "common.h"

#include "common.h"

extern u8 D_80082E6A[9];
extern s16 D_8006ADE8[5];
extern s32 func_80034FE4(void *arg0);

/* Returns the check result in mode 2, otherwise whether the check or fallback status is nonzero. */
s32 func_80034FFC(void *context) {
    s32 result;

    if (D_80082E6A[0] != 2) {
        result = 0;
        if (func_80034FE4(context) != 0) {
            result = 1;
        } else {
            s16 *fallback_status = D_8006ADE8;
            if (*fallback_status != 0) {
                result = 1;
            }
        }
        return result;
    }

    return func_80034FE4(context);
}
