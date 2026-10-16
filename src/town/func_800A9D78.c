#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
void townHandleInsertInitializeTwoValuesStatusFlags();     /* extern */
void townInitializeOptionalObjectState(); /* extern */
extern M2C_UNK D_800D0690;
extern M2C_UNK D_800D0E04;
extern M2C_UNK D_800D6A58;

/* Initialize the object's sprite, scene data, and behavior. */
void townInitializeEmoteSpriteAndScene(s32 object, s32 scene, s32 sprite) {
    func_8003DB94(sprite, &D_800D0E04, 0);
    townHandleInsertInitializeTwoValuesStatusFlags(object, scene, &D_800D6A58);
    townInitializeOptionalObjectState(object, scene, sprite, &D_800D0690);
}
