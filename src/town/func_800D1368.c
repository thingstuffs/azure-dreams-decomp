#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CEB00();                            /* extern */
extern s8 D_80082688;

typedef struct S_800CEAC8_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800CEAC8_0;   /* arg0 in func_800CEAC8 */

void func_800CEAC8(S_800CEAC8_0 *arg0) {
    func_800CEB00();
    D_80082688 = 0;
    arg0->unk_90 = 4;
}
