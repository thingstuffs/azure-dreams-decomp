#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80093D18();       /* extern */
M2C_UNK func_80093D48();       /* extern */
M2C_UNK func_80094984();       /* extern */
s32 func_80094B0C();           /* extern */
M2C_UNK func_80095094();       /* extern */
M2C_UNK func_8009550C();       /* extern */
M2C_UNK func_80095C80();       /* extern */
M2C_UNK func_80099754();       /* extern */
void func_800933E0(void);      /* extern */
extern M2C_UNK D_800D0078;
extern s32 D_800FE518;

typedef struct S_80093328_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80093328_0;   /* arg0 in func_80093328 */

void func_80093328(void *arg0, void *arg1, s32 arg2) {
    s16 temp_v0;

    func_80095C80(arg1);
    func_80095094(arg1);
    temp_v0 = ((S_80093328_0 *)arg0)->unk_0A - 1;
    ((S_80093328_0 *)arg0)->unk_0A = temp_v0;
    if (temp_v0 < 0) {
        func_80099754(arg1);
        func_8009550C(arg1);
        if (D_800FE518 != 0 && func_80094B0C(arg0 - 0x20) != 0) {
            func_80094984(&D_800D0078, arg0, arg2);
            func_80093D18(arg0, arg1, arg2);
            return;
        }
        func_80093D48(arg0, arg1, arg2);
    }
}
