#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                      /* extern */
void townInitializePlayerLinkedRecord();        /* extern */


/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void townAdvancePlayerState(s32 context, EntityRec *state, s32 updateData) {
    state->z.v = (s32) (state->z.v + state->flags14);
    townAddHex20000SSignedOffsetHex14(state);
    if (state->flags14 >= 0) {
        townInitializePlayerLinkedRecord(context, state, updateData);
    }
}
