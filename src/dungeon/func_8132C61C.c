#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173E1C_0 {
    u8 pad_00[0x360C];
    u8 unk_360C;
} S_80173E1C_0;   /* (arg0 + 0x80010000) in func_80173E1C */

s32 func_80173E1C(s32 arg0, s32 arg1) {
    return ((S_80173E1C_0 *)((arg0 + 0x80010000)))->unk_360C != arg1;
}
