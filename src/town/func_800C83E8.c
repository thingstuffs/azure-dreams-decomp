#include "common.h"
#include "m2c_compat.h"

extern s32 D_80083788;
extern M2C_UNK D_800C5BA8;
extern s32 D_800D0428;

typedef struct S_800C5B48_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C5B48_0;   /* arg1 in func_800C5B48 */

typedef struct S_800C5B48_1 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C5B48_1;   /* arg0 in func_800C5B48 */

void func_800C5B48(S_800C5B48_1 *arg0, S_800C5B48_0 *arg1) {
    s32 temp_a0;
    u16 temp_v0;

    temp_a0 = arg1->unk_08;
    arg1->unk_08 = (s32) (temp_a0 + ((s32) ((D_80083788 + D_800D0428) - temp_a0) / 2));
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_54 = &D_800C5BA8;
    }
}
