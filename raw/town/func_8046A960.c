#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 *D_8001E950;
extern s32 func_8001A73C(void);

s32 func_8001B960(void *arg0, s32 arg1) {
    if (D_8001E950[5] == 0) {
        FIELD((arg1 * 0x10) + FIELD(arg0, s32, 0x10), s32, 8) =
            func_8001A73C();
        return 0;
    }
    return 1;
}
