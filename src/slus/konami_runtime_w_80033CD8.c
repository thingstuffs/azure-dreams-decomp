#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033CD8_0_pre {
    s32 unk_00;
    u8 pad_04[0x8];
} S_80033CD8_0_pre;   /* the 0xC bytes before arg0 in func_80033CD8, addressed as arg0[-1] */


M2C_UNK func_8004491C();                      /* extern */

/* Call func_8004491C on the block header when the preceding status is zero. */
void func_80033CD8(void *block_data) {
    if (((S_80033CD8_0_pre *)block_data)[-1].unk_00 == 0) {
        func_8004491C(block_data - 0x20);
    }
}
