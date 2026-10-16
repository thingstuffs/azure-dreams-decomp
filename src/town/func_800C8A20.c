#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

M2C_UNK func_8003DB94(); /* extern */
void townHandleInsertInitializeTwoValuesStatusFlags();  /* extern */
void townInitializeOptionalObjectState(); /* extern */
extern s32 D_800D0678[];
extern M2C_UNK D_800D0690;
extern u8 D_800ED15C[];


/* Initialize the object's sprite and behavior, then set its state bytes. */
void func_800C6180(Rec_D_800CFCB4 *object, s32 context, s32 sprite) {
    func_8003DB94(sprite, &D_800ED15C, 0);
    townHandleInsertInitializeTwoValuesStatusFlags(object, context, &D_800D0678);
    townInitializeOptionalObjectState(object, context, sprite, &D_800D0690);
    object->unk_4D.as_s8 = 0xD;
    object->unk_4C = 7;
}
