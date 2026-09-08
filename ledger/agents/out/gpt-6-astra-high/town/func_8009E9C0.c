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

/* Clear status and values, then initialize the state's data pointer and mode. */
void func_8009C120(S_8009C120_2 *state, S_8009C120_0 *status, S_8009C120_1 *values) {
    status->unk_15 = 0;
    values->unk_0C = 0;
    values->unk_10 = 0;
    values->unk_14 = 0;
    state->unk_50 = &D_8009B828;
    state->unk_6C = 7;
}
