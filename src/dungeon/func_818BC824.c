#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 dungeonTryTriggerTargetRecordEffect(s32, s32);                 /* extern */
void dungeonApplyClampedActorValueDelta();                      /* extern */
s16 dungeonCapPendingActorValueDelta();                      /* extern */
void *createActorValuePopup(); /* extern */


/* Adds 0x200 to the object's unk_64 and runs callbacks when its mode-2 check returns zero. */
void dungeonAddHex200SField64RunsCallbacksModeN2CheckReturnsZero(EntityRec *object) {
    if (dungeonTryTriggerTargetRecordEffect((s32)object, 2) == 0) {
        object->unk_64 = (u16) (((u16)object->unk_64) + 0x200);
        dungeonCapPendingActorValueDelta(object);
        createActorValuePopup(0x8004, object, (s16) ((u16)object->unk_64), 1);
        dungeonApplyClampedActorValueDelta(object);
    }
}
