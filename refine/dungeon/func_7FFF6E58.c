#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984(); /* extern */
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in func_800945B8 */

/* Initializes the state and sets the output pointer to D_80092CD4. */
void func_800945B8(M2C_UNK **outputSlot, S_800945B8_0 *state, M2C_UNK initContext) {
    register M2C_UNK entryOutputSlot ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK entryState ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK entryInitContext ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
    M2C_UNK forwardedExtraArgument;
    func_800948DC(entryOutputSlot, entryState, entryInitContext, forwardedExtraArgument);
    state->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D0140, outputSlot, initContext);
    *outputSlot = &D_80092CD4;
}
