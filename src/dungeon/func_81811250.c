#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E99C();                         /* extern */

typedef struct S_80026250_0 {
    u8 pad_00[0x14];
    s32 * unk_14;
} S_80026250_0;   /* arg0 in func_80026250 */

void func_80026250(S_80026250_0 *arg0) {
    func_8004E99C(*arg0->unk_14);
    *arg0->unk_14 = 0;
}
