#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_8009A1A4();        /* extern */

typedef struct S_80099B00_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80099B00_0;   /* arg1 in func_80099B00 */

void func_80099B00(s32 arg0, S_80099B00_0 *arg1, M2C_UNK arg2) {
    arg1->unk_08 = (s32) (arg1->unk_08 + arg1->unk_14);
    func_80095388(arg1);
    if (arg1->unk_14 >= 0) {
        func_8009A1A4(arg0, arg1, arg2);
    }
}
