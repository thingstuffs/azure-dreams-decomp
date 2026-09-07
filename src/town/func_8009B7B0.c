#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_800982EC;

typedef struct S_80098F10_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098F10_0;   /* arg0 in func_80098F10 */

void func_80098F10(S_80098F10_0 *arg0, M2C_UNK arg1) {
    func_80099754(arg1);
    arg0->unk_04 = &D_800982EC;
}
