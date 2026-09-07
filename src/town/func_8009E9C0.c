#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8009B828;

typedef struct S_8009C120_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009C120_0;   /* arg1 in func_8009C120 */

typedef struct S_8009C120_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C120_1;   /* arg2 in func_8009C120 */

typedef struct S_8009C120_2 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009C120_2;   /* arg0 in func_8009C120 */

void func_8009C120(S_8009C120_2 *arg0, S_8009C120_0 *arg1, S_8009C120_1 *arg2) {
    arg1->unk_15 = 0;
    arg2->unk_0C = 0;
    arg2->unk_10 = 0;
    arg2->unk_14 = 0;
    arg0->unk_50 = &D_8009B828;
    arg0->unk_6C = 7;
}
