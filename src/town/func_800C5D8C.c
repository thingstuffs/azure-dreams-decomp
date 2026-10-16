#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 townSelectObjectSetupPath(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
void townChooseRandomMovementDirection();    /* extern */


/* Count down after an unhandled entity update and choose a direction when the timer expires. */
void townRunUnhandledUpdateAndChooseDirection(Rec_func_80094268_arg0 *entity, M2C_UNK motion, M2C_UNK context, s32 update_arg) {
    u16 ticks_left;

    if (townSelectObjectSetupPath(entity, motion, context, update_arg) == 0) {
        ticks_left = entity->unk_6C.as_u16 - 1;
        entity->unk_6C.as_u16 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            townChooseRandomMovementDirection(entity, motion, context);
        }
    }
}
