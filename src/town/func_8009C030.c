#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098928();     /* extern */
M2C_UNK func_80099858();                            /* extern */
s16 func_800C2AE8();                          /* extern */

typedef struct S_80099790_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80099790_0;   /* arg1 in func_80099790 */

typedef struct S_80099790_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
} S_80099790_1;   /* arg0 in func_80099790 */

void func_80099790(S_80099790_1 *arg0, S_80099790_0 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_0A = func_800C2AE8(arg1);
    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg1->unk_02 = (u16) arg0->unk_30;
        arg1->unk_06 = (u16) arg0->unk_32;
        arg0->unk_10 = (u16) arg0->unk_0E;
        func_80098928(arg0, arg1, arg2);
        return;
    }
    arg1->unk_02 = (u16) (arg1->unk_02 + ((s32) ((s16) arg0->unk_30 - (s16) arg1->unk_02) / (s16) temp_v0));
    arg1->unk_06 = (u16) (arg1->unk_06 + ((s32) ((s16) arg0->unk_32 - (s16) arg1->unk_06) / (s16) arg0->unk_0A));
}
