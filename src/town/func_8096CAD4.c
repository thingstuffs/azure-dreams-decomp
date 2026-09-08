#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80124F6C_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_80124F6C_0;   /* arg0 in func_80124F6C */


M2C_UNK func_801248C0(S_80124F6C_0 *);
/* Initialize the state fields before calling func_801248C0. */
void func_80124F6C(S_80124F6C_0 *state) {
    state->unk_0A = 8;
    state->unk_04 = 0;
    state->unk_06 = 0;
    func_801248C0(state);
}
