#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8009E994;

typedef struct S_8009EB20_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009EB20_0;   /* arg1 in func_8009EB20 */

typedef struct S_8009EB20_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009EB20_1;   /* arg0 in func_8009EB20 */

void func_8009EB20(S_8009EB20_1 *arg0, S_8009EB20_0 *arg1) {
    arg1->unk_15 = 0;
    arg0->unk_50 = &D_8009E994;
    arg0->unk_6C = 8;
}
