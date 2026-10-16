#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townCallTheHandlerSelectsNonzeroEntry();  /* extern */
void townStoreTheValidSharedAngleInOffsetHex10(Rec_func_80094268_arg0 *);                            /* extern */
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();                     /* extern */
extern s32 D_80091260;
extern M2C_UNK D_800D0090;


/* Set up the entity state and motion, then install its handler table. */
void townInitializeMotionAction(Rec_func_80094268_arg0 *entity, s32 motion, s32 value) {
    entity->unk_3E.as_s16 = 6;
    townStoreTheValidSharedAngleInOffsetHex10(entity);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(motion);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0090, entity, value);
    entity->unk_00.as_pm = &D_80091260;
}
