#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098928();     /* extern */
M2C_UNK func_80099904();                            /* extern */
s16 func_800C2AE8();                          
typedef struct S_80099894_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80099894_0;   /* arg1 in func_80099894 */

typedef struct S_80099894_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80099894_1;   /* arg0 in func_80099894 */

/* extern */

void func_80099894(S_80099894_1 *arg0, S_80099894_0 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_0A = func_800C2AE8(arg1);
    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((s16) temp_v0 < 0) {
        func_80098928(arg0, arg1, arg2);
        func_80099904();
        return;
    }
    arg1->unk_04 = (s32) (arg1->unk_04 + 0xFFFE0000);
}
