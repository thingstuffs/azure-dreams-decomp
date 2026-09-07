#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A78AC_0_pre {
    u16 unk_00;
} S_800A78AC_0_pre;   /* the 0x2 bytes before arg0 in func_800A78AC, addressed as arg0[-1] */

typedef struct S_800A78AC_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)();
} S_800A78AC_0;   /* arg0 in func_800A78AC */


M2C_UNK func_800478B8();                     /* extern */

void func_800A78AC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK (*temp_v0)();

    temp_v0 = ((S_800A78AC_0 *)arg0)->unk_50;
    if (temp_v0 != NULL) {
        temp_v0();
        if (!(((S_800A78AC_0_pre *)arg0)[-1].unk_00 & 0x8000)) {
            func_800478B8(arg2);
        }
    }
}
