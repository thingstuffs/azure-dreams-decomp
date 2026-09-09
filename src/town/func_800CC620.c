#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
/* extern */

typedef struct S_800C9D80_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C9D80_0;   /* arg0 in func_800C9D80 */


M2C_UNK func_800C9C94(S_800C9D80_0 *, s32, s32);
void func_800C9D80(S_800C9D80_0 *arg0, s32 arg1, s32 arg2) {
    func_800C9C94(arg0, arg1, arg2);
    arg0->unk_90 = (s16) (func_800374F4(3) + 1);
}
