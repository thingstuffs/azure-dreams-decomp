#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984(); /* extern */
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;


/* Initializes the state and sets the output pointer to D_80092CD4. */
void func_800945B8(M2C_UNK **outputSlot, Rec_D_800E3D7C *state, M2C_UNK initContext) {
    register M2C_UNK entryOutputSlot ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register M2C_UNK entryState ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register M2C_UNK entryInitContext ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    M2C_UNK forwardedExtraArgument;
    func_800948DC(entryOutputSlot, entryState, entryInitContext, forwardedExtraArgument);
    state->unk_14.as_s32 = 0xFFEF0000;
    func_80094984(&D_800D0140, outputSlot, initContext);
    *outputSlot = &D_80092CD4;
}
