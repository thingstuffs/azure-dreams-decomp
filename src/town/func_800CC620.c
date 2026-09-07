#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C9C94();                            /* extern */

typedef struct S_800C9D80_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C9D80_0;   /* arg0 in func_800C9D80 */

void func_800C9D80(S_800C9D80_0 *arg0) {
    func_800C9C94();
    arg0->unk_90 = (s16) (func_800374F4(3) + 1);
}
