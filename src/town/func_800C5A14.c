#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033D08();                      /* extern */
void townUnlinkSceneListNode();                      /* extern */
s32 townClassifyObjectAgainstBounds(Rec_func_80094268_arg0 *, s32);                                /* extern */
void townClearObjectSlotAndMarkRemoved();                      /* extern */
void townUpdateObjectMotionAndFlags();    /* extern */
extern M2C_UNK D_800C3960;


/* Update the object motion or clear its state and clean it up when the position check fails. */
void townUpdateObjectPositionOrCleanup(Rec_func_80094268_arg0 *object, s32 position, s32 motion) {
    s32 check_result;
    s8 *state_flag;

    check_result = townClassifyObjectAgainstBounds(object, position);
    if (check_result != 0) {
        if ((check_result != 2) || (object->unk_50.as_s32 != &D_800C3960)) {
            townUnlinkSceneListNode(object);
            state_flag = object->unk_98;
            if (state_flag != NULL) {
                *state_flag = 0;
            }
            func_80033D08(object);
            townClearObjectSlotAndMarkRemoved(object);
            return;
        }
        townUpdateObjectMotionAndFlags(object, position, motion);
        return;
    }
    townUpdateObjectMotionAndFlags(object, position, motion);
}
