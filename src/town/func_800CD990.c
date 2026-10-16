#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townApplyObjectSetupAndUpdate();    /* extern */
M2C_UNK assignObjectDataPointers(Rec_func_80094268_arg0 *);                            /* extern */
s32 townCreateAndInvokeRenderObject();                  /* extern */


/* Decrement the entity countdown and run its completion handlers when it expires. */
void townUpdateEntityCountdownCompletion(Rec_func_80094268_arg0 *entity, s32 completion_arg1, s32 completion_arg2) {
    u16 countdown;

    countdown = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        assignObjectDataPointers(entity);
        townCreateAndInvokeRenderObject(entity, entity->unk_96.as_u8);
        townApplyObjectSetupAndUpdate(entity, completion_arg1, completion_arg2);
    }
}
