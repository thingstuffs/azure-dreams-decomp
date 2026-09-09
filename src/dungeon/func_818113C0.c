#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 func_8004DC14();                /* extern */

typedef struct S_800263C0_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_800263C0_0;   /* arg0 in func_800263C0 */


M2C_UNK func_80026B44(S_800263C0_0 *, M2C_UNK, s32, s32);
/* Initialize the object and store the source lookup result through its output pointer. */
void func_800263C0(S_800263C0_0 *object, M2C_UNK source, s32 init_value, s32 init_value_2) {
    func_80026B44(object, source, init_value, init_value_2);
    *object->unk_0C = func_8004DC14(source, 0);
}
