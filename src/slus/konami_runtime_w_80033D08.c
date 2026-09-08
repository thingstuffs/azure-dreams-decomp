#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033D08_0_pre {
    s32 unk_00;
    u8 pad_04[0x8];
} S_80033D08_0_pre;   /* the 0xC bytes before arg0 in func_80033D08, addressed as arg0[-1] */


M2C_UNK func_80044A50();                      /* extern */

/* Unlinks the enclosing block when its header field is nonzero. */
void func_80033D08(void *block_data) {
    if (((S_80033D08_0_pre *)block_data)[-1].unk_00 != 0) {
        func_80044A50(block_data - 0x20);
    }
}
