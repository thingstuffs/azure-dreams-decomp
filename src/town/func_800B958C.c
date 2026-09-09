#include "common.h"

extern s32 func_80042900(void *, s8);
extern s32 func_800B5E10(s32);
extern s32 func_80049E88(void *);

/* Returns a mapped code for the object, or its fallback value when the code is zero. */
s32 func_800B6CEC(void *object) {
    s32 code = *((u8 *) object + 0x13);

    if (code != 0) {
        if ((func_80042900(object, 10) << 0x10) != 0) {
            code = 47;
        } else {
            code = func_800B5E10(code);
        }
        return code;
    }
    return func_80049E88(object);
}
