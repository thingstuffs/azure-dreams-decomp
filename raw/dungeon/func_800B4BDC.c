#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800BA37C(void);

s32 func_800BA33C(void *arg0) {
    register s32 code ASM_REG("$2");
    code = 0x18;
    if ((arg0 == NULL) || ((M2C_FIELD(arg0, u8 *, 0x13) == code) && (M2C_FIELD(arg0, u8 *, 0xB5) == 1))) {
        func_800BA37C();
        return 0;
    }
    if ((M2C_FIELD(arg0, s32 *, 0x1C) & 0x20000)) {
        return 1;
    }
    return 0;
}
