/* Relink of matched town/func_800A9DF4; every changed retail word is a paired relocation. */
#define D_800D0E04 D_800ED15C
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
void townInitializeOptionalObjectState(); /* extern */
extern M2C_UNK D_800ED15C;

/* Initialize the object's animation data and default behavior. */
void func_800C620C(s32 object, M2C_UNK updateContext, M2C_UNK animationState) {
    func_8003DB94(animationState, &D_800ED15C, 0);
    townInitializeOptionalObjectState(object, updateContext, animationState, 0);
}
