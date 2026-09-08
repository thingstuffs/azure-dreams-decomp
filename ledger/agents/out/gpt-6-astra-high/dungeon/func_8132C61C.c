#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173E1C_0 {
    u8 pad_00[0x360C];
    u8 unk_360C;
} S_80173E1C_0;   /* (arg0 + 0x80010000) in func_80173E1C */

/* Return whether the byte at the given offset differs from the expected value. */
s32 func_80173E1C(s32 byte_offset, s32 expected_value) {
    return ((S_80173E1C_0 *)((byte_offset + 0x80010000)))->unk_360C != expected_value;
}
