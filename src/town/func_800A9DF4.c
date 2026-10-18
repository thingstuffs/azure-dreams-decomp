#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
void initialize_optional_object_state(); /* extern */
extern M2C_UNK D_800D0E04;

/* Initialize the object's animation data and default behavior. */
void initialize_emote_animation(s32 object, M2C_UNK updateContext, M2C_UNK animationState) {
    func_8003DB94(animationState, &D_800D0E04, 0);
    initialize_optional_object_state(object, updateContext, animationState, 0);
}
