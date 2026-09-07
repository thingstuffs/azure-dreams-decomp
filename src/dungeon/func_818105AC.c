#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026340();                         /* extern */

typedef struct S_800255AC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800255AC_0;   /* arg0 in func_800255AC */

void func_800255AC(S_800255AC_0 *arg0) {
    func_80026340(arg0->unk_40);
}
