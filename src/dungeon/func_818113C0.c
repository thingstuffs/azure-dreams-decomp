#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 func_8004DC14();                /* extern */

typedef struct S_800263C0_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_800263C0_0;   /* arg0 in func_800263C0 */


M2C_UNK func_80026B44(S_800263C0_0 *, M2C_UNK, s32, s32);
void func_800263C0(S_800263C0_0 *arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    func_80026B44(arg0, arg1, arg2, arg3);
    *arg0->unk_0C = func_8004DC14(arg1, 0);
}
