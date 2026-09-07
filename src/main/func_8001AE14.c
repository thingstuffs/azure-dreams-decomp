#include "common.h"

extern u8 D_8009DDD8[];

s32 func_8001AE14(s32 arg0) {
    return *(s32 *)(D_8009DDD8 + (arg0 << 7));
}
