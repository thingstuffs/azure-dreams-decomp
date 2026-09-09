#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800C30E0(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_800C382C();    /* extern */


/* Count down after an unhandled entity update and choose a direction when the timer expires. */
void func_800C34EC(Rec_func_80094268_arg0 *entity, M2C_UNK motion, M2C_UNK context, s32 update_arg) {
    u16 ticks_left;

    if (func_800C30E0(entity, motion, context, update_arg) == 0) {
        ticks_left = entity->unk_6C.as_u16 - 1;
        entity->unk_6C.as_u16 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            func_800C382C(entity, motion, context);
        }
    }
}
