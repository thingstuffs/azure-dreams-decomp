#include "common.h"
#include "m2c_compat.h"

s32 func_80003AE0(void) {
    return *(s32 *)0x45F8 + M2C_FIELD((M2C_FIELD(*(void **)0x3F54, s8 *, 0x4130) * 4), s32 *, 0x4124);
}
