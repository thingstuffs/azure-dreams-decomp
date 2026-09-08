#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_800BA33C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x95];
    u8 unk_B5;
} S_800BA33C_0;   /* arg0 in func_800BA33C */

s32 func_800BA33C(S_800BA33C_0 *arg0) {
    register s32 code ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    code = 0x18;
    if ((arg0 == NULL) || ((arg0->unk_13 == code) && (arg0->unk_B5 == 1))) {
        return 0;
    }
    if ((arg0->unk_1C & 0x20000)) {
        return 1;
    }
    return 0;
}
