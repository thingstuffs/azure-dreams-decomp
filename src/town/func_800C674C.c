#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void townAddHex20000SSignedOffsetHex14();                      /* extern */
s16 townGetClampedTransformCoordinate();                          /* extern */
void townApplyObjectSetupAndUpdate();

/* extern */

/* Advance the object's fixed-point value and clamp it when it exceeds the limit. */
void townAdvanceAndClampEntityValue(s32 context, EntityRec *object, s32 update_data) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (townGetClampedTransformCoordinate(object) < object->z.w.i) {
        object->z.w.i = townGetClampedTransformCoordinate(object);
        townApplyObjectSetupAndUpdate(context, object, update_data);
        return;
    }
    townAddHex20000SSignedOffsetHex14(object);
}
