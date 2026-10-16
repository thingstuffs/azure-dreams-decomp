#include "common.h"
#include "m2c_compat.h"

s32 func_807018AC(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    if (arg0 != 0) {
        if (arg0 != 1) {
            var_v0 = arg0;
            if (arg0 < 0) {
                var_v0 = arg0 + 0x1F;
            }
            temp_v0 = var_v0 >> 5;
            return (1 << (arg0 - (temp_v0 << 5))) & *((temp_v0 * 4) + *(s32 *)0x80701968);
        }
        return 1;
    }
    return 0;
}
