#include "common.h"

#include "common.h"

extern s32 func_8003C5A4(s32 arg0);
extern s32 D_8006B1A8[];

s32 func_8003C5F0(s32 arg0) {
    s32 index = func_8003C5A4(arg0);

    if (index < 0) {
        return 0;
    }

    return D_8006B1A8[index];
}
