#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scaleRandomToUnsignedHalfwordLimit();                         /* extern */
s32 *townGetSmallestSignedOverlapAxisAmountTwoIntersectingBoxes();              /* extern */
s32 townSelectObjectSetupPath(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
void townInitializeObjectAndDataPointer();    /* extern */
M2C_UNK func_800CDE4C();    /* extern */
extern M2C_UNK D_800CFCB4;

/* Count down when the object is ready and choose its next setup when the timer expires. */
void townCountDownAndSelectNextSetup(Rec_func_80094268_arg0 *object, M2C_UNK request_data, M2C_UNK request_param, s32 check_param) {
    s32 *state;
    u16 ticks_left;

    if ((townSelectObjectSetupPath(object, request_data, request_param, check_param) == 0) &&
        ((state = townGetSmallestSignedOverlapAxisAmountTwoIntersectingBoxes(object, &D_800CFCB4), (state == NULL)) || (*state == 2)) &&
        (ticks_left = object->unk_6C.as_u16 - 1,
         object->unk_6C.as_u16 = ticks_left, ((ticks_left << 0x10) <= 0))) {
        if (scaleRandomToUnsignedHalfwordLimit(2) & 0xFFFF) {
            townInitializeObjectAndDataPointer(object, request_data, request_param);
            return;
        }
        func_800CDE4C(object, request_data, request_param);
    }
}
