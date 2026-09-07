#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800954C4();                            /* extern */
extern s8 D_800CFCEB;

typedef struct S_800966C8_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800966C8_0;   /* arg0 in func_800966C8 */

void func_800966C8(S_800966C8_0 *arg0, s32 arg1) {
    D_800CFCEB = 1;
    arg0->unk_00 = arg1;
    arg0->unk_0C = 0;
    func_800954C4();
}
