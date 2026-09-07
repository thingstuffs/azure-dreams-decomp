#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E99C();                         /* extern */

typedef struct S_80026B44_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_80026B44_0;   /* arg0 in func_80026B44 */

void func_80026B44(S_80026B44_0 *arg0) {
    s32 temp_a0;

    temp_a0 = *arg0->unk_0C;
    if (temp_a0 != 0) {
        func_8004E99C(temp_a0);
        *arg0->unk_0C = 0;
    }
}
