#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033CD8_0_pre {
    s32 unk_00;
    u8 pad_04[0x8];
} S_80033CD8_0_pre;   /* the 0xC bytes before arg0 in func_80033CD8, addressed as arg0[-1] */


M2C_UNK func_8004491C();                      /* extern */

void func_80033CD8(void *arg0) {
    if (((S_80033CD8_0_pre *)arg0)[-1].unk_00 == 0) {
        func_8004491C(arg0 - 0x20);
    }
}
