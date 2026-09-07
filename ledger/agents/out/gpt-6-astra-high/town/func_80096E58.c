#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984(); /* extern */
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in func_800945B8 */

/* Initialize state and set the output pointer to the shared data. */
void func_800945B8(M2C_UNK **outputData, S_800945B8_0 *state, M2C_UNK setupValue) {
    func_800948DC();
    state->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D0140, outputData, setupValue);
    *outputData = &D_80092CD4;
}
