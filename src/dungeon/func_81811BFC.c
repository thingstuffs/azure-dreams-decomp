#include "common.h"

/* Returns whether the object exists and its field at offset 0x28 is zero. */
u32 func_80026BFC(void *object) {
    if (object != 0) {
        if (*(s32 *)((s8 *)object + 0x28) == 0) {
            return 1;
        }
    }
    return 0;
}
