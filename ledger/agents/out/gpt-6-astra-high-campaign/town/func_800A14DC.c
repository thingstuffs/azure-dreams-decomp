#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009EC3C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009EC3C_0;   /* arg1 in func_8009EC3C */

typedef struct S_8009EC3C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009EC3C_1;   /* arg2 in func_8009EC3C */

typedef struct S_8009EC3C_2 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    M2C_UNK * unk_60;
    u8 pad_64[0x18];
    s16 unk_7C;
} S_8009EC3C_2;   /* arg0 in func_8009EC3C; pointer addresses record offset 0x10 */


extern M2C_UNK D_8009DE28;
extern M2C_UNK D_8009ECF0;

/* Clear the state fields and initialize the record handlers and mode. */
void func_8009EC3C(void *record_data, S_8009EC3C_0 *state, S_8009EC3C_1 *values) {
    state->unk_15 = 0;
    values->unk_0C = 0;
    values->unk_10 = 0;
    values->unk_14 = 0;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_60 = &D_8009ECF0;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_7C = 7;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_00 = &D_8009DE28;
}
