#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800C283C;
extern s32 D_800FE4A0;

typedef struct S_800C2864_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    M2C_UNK * unk_50;
} S_800C2864_0;   /* arg0 in func_800C2864 */

void func_800C2864(S_800C2864_0 *arg0) {
    if (D_800FE4A0 != arg0) {
        arg0->unk_14 = 1;
        arg0->unk_50 = &D_800C283C;
    }
}
