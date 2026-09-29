#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*Callback)(s32);

extern s32 func_8001A5D0(void);

/* Check whether the object callback returns 2 when the prerequisite value is at least 2. */
s32 func_8001C5CC(void) {
    s32 callback_result;

    if (func_8001A5D0() >= 2) {
        callback_result = (*(Callback *)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x2D4))(0);
        if (callback_result == 2)
            return 1;
    }
    return 0;
}
