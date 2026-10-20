#include "common.h"
#include "m2c_compat.h"

extern s32 D_8001B0D4;
s32 get_secondary_price(void) {
    return D_8001B0D4;
}
