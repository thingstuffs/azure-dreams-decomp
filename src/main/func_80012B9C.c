#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025D34();                         /* extern */
M2C_UNK func_80027AFC();                /* extern */

typedef struct S_80025B9C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B9C_0;   /* arg0 in func_80025B9C */

void func_80025B9C(void *arg0) {
    func_80025D34(arg0 - 0x20);
    func_80027AFC(((S_80025B9C_0 *)arg0)->unk_20, 0);
}
