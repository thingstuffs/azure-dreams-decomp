#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80049490();                         /* extern */

typedef struct S_800ADB04_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x18];
    s32 unk_20;
} S_800ADB04_0;   /* arg0 in func_800ADB04 */

void func_800ADB04(S_800ADB04_0 *arg0) {
    func_80049490(arg0->unk_20 + (arg0->unk_04 * 4));
}
