#include "common.h"

u32 func_80026BFC(void *arg0) {
    if (arg0 != 0) {
        if (*(s32 *)((s8 *)arg0 + 0x28) == 0) {
            return 1;
        }
    }
    return 0;
}
