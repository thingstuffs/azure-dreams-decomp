#include "modules/town_door.h"

/* Tests the input and object angle against either supported global state. */
s32 townCheckDoorInputAndAngle(Rec_func_800A0668_arg0 *object, s32 test_value) {
    if (townGetSmallestSignedOverlapAxisAmountTwoIntersectingBoxes(test_value, &D_800CFCB4) != 0) {
        s32 *global_base = &D_800834B8;
        s32 global_angle = ((S_800A0F10_0 *)global_base)->unk_10 & 0xFFF;
        s32 object_angle = object->unk_72 & 0xFFF;

        if ((u32) ((object_angle - global_angle) + 0x3FF) < 0x7FFU) {
            if ((D_800834B8 == (s32)&D_80091260) || (D_800834B8 == (s32)&D_80091528)) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
