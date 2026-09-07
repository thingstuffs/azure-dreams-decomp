#include "common.h"

extern u8 D_80081484[];
extern u8 D_80081470[];
s16 func_80098C48();

s32 func_80098C80(s32 arg0) {
    s32 var_v0;

    var_v0 = (s16)func_80098C48();
    if (var_v0 >= 0) {
        var_v0++;
        return (s16)var_v0;
    }
    if (arg0 == D_80081484) {
        return 0x15;
    }
    if (arg0 == D_80081470) {
        return 0x16;
    }
    return 0;
}
