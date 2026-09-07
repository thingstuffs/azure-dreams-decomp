#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8();                      /* extern */

typedef struct S_80DE6A54_0 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80DE6A54_0;   /* arg2 in func_80DE6A54 */

void func_80DE6A54(u16 *arg0, M2C_UNK arg1, S_80DE6A54_0 *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = *arg0 + 1;
    *arg0 = temp_v0;
    if ((s16) temp_v0 < 9) {
        temp_v0_2 = arg2->unk_1E + 0x100;
        arg2->unk_1E = temp_v0_2;
        arg2->unk_1C = temp_v0_2;
    }
    func_800478B8(arg2);
}
