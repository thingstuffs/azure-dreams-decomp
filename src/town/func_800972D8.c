#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800949C4();                         /* extern */

typedef struct S_80094A38_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
} S_80094A38_0;   /* arg1 in func_80094A38 */

void func_80094A38(s32 arg0, S_80094A38_0 *arg1) {
    arg1->unk_1C = arg0;
    func_800949C4(arg0, arg1->unk_10);
}
