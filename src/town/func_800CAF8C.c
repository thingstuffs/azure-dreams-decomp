#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void townAddHex20000SSignedOffsetHex14();                      /* extern */
s16 townQueryLoweredTransformPosition();                          /* extern */
void townApplyObjectSetupAndUpdate();        /* extern */

/* extern */

/* Advance the object's position and stop its movement when it exceeds the limit. */
void func_800C86EC(s32 context, EntityRec *object, s32 finish_arg) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (townQueryLoweredTransformPosition(object) < object->z.w.i) {
        object->z.w.i = townQueryLoweredTransformPosition(object);
        object->flags14 = 0;
        townApplyObjectSetupAndUpdate(context, object, finish_arg);
        return;
    }
    townAddHex20000SSignedOffsetHex14(object);
}
