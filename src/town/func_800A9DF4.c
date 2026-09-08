#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0E04;

/* Initialize the object's animation data and default behavior. */
void func_800A7554(s32 object, M2C_UNK updateContext, M2C_UNK animationState) {
    func_8003DB94(animationState, &D_800D0E04, 0);
    func_8009B218(object, updateContext, animationState, 0);
}
