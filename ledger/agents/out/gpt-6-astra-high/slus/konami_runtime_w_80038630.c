#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038630_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x13];
    s8 unk_27;
    u8 pad_28[0x5C];
    s8 unk_84;
} S_80038630_0;   /* arg0 in func_80038630 */


extern M2C_UNK func_80038648;

/* Clears two state fields and sets the next handler to func_80038648. */
void func_80038630(S_80038630_0 *state) {
    state->unk_27 = 0;
    state->unk_84 = 0;
    state->unk_10 = &func_80038648;
}
