#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                      /* extern */
M2C_UNK func_800CE04C();     /* extern */

typedef struct S_800CDC2C_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800CDC2C_0;   /* arg0 in townAdvanceObjectAndRunFollowUp */


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void townAdvanceObjectAndRunFollowUp(S_800CDC2C_0 *object, EntityRec *motion, M2C_UNK context) {
    object->unk_72 = (u16) (object->unk_72 + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    townAddHex20000SSignedOffsetHex14(motion);
    if (motion->flags14 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
