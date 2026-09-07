#include "common.h"

extern s32 D_80083E98[];

s32 func_80021D38(s32 arg0) {
    return D_80083E98[arg0 * 32];
}
