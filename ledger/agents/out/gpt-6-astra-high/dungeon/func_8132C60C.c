#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173E0C_0 {
    u8 pad_00[0x360C];
    s8 unk_360C;
} S_80173E0C_0;   /* (arg0 + 0x80010000) in func_80173E0C */

/* Stores a byte at the given offset from 0x8001360C. */
void func_80173E0C(s32 offset, s8 value) {
    ((S_80173E0C_0 *)((offset + 0x80010000)))->unk_360C = value;
}
