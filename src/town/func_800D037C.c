#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
s32 func_800C30E0();         /* extern */
M2C_UNK func_800CDF00();     /* extern */
M2C_UNK func_800CDF94();


/* extern */

/* Advance motion, clamp at its limit, and handle the remaining steps. */
void func_800CDADC(Rec_func_80094268_arg0 *entity, EntityRec *motion, M2C_UNK context) {
    u16 steps_left;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (func_800C2AE8(motion) < motion->z.w.i) {
        motion->z.w.i = func_800C2AE8(motion);
        steps_left = entity->unk_90.as_u16 - 1;
        entity->unk_90.as_u16 = steps_left;
        if ((steps_left << 0x10) <= 0) {
            motion->flags14 = 0;
            func_800CDF94(entity, motion, context);
            return;
        }
        if (func_800C30E0(entity, motion, context) == 0) {
            func_800CDF00(entity, motion, context);
            return;
        }
    } else {
        func_80095388(motion);
    }
}
