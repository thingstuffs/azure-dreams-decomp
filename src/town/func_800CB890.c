#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
M2C_UNK func_800C9068();                            /* extern */
extern M2C_UNK D_800C907C;
extern M2C_UNK D_800D6268;


typedef struct S_800C8FF0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
} S_800C8FF0_0;   /* arg0 in func_800C8FF0 */

typedef struct S_800C8FF0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C8FF0_1;   /* arg1 in func_800C8FF0 */

void func_800C8FF0(S_800C8FF0_0 *arg0, S_800C8FF0_1 *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    M2C_UNK temp_v1;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    temp_v1 = arg2;
    if ((s16) temp_v0 < 0) {
        func_800C2E84(arg0, temp_v1, &D_800D6268);
        arg0->unk_6C = 3U;
        arg0->unk_50 = &D_800C907C;
        arg0->unk_72 = 0xC00;
        func_800C9068();
        return;
    }
    arg0->unk_72 = 0x800;
    arg1->unk_04 = (s32) (arg1->unk_04 + 0xFFEAAAAB);
}
