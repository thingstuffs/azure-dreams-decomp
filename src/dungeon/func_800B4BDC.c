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

/* Test flag 0x20000 for a valid object outside the excluded state. */
s32 func_800BA33C(S_800BA33C_0 *object) {
    s32 code;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if ((object == NULL) || ((object->unk_13 == 0x18) && (object->unk_B5 == 1))) {
        return 0;
    }
    if ((object->unk_1C & 0x20000)) {
        return 1;
    }
    return 0;
}
