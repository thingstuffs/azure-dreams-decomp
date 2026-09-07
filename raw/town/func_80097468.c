#include "common.h"

extern s32 D_80083168;
extern s32 func_80094B58(s32);
extern s32 func_80094C08(void);

s32 func_80094BC8(s32 arg0, s32 arg1) {
    register s32 payload ASM_REG("$2");
    s32 result;

    result = func_80094B58(D_80083168);
    if ((s16)result == -1) {
        return -1;
    }
    payload = result + arg1;
    ASM_KEEP(payload);
    func_80094C08();
    return payload & 0xFFF;
}
