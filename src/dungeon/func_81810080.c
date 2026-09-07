#include "common.h"

extern u32 strlen(s32 value);
extern s32 D_8002946C[];

u32 func_80025080(s32 arg0) {
    return strlen(D_8002946C[arg0]) >> 1;
}
