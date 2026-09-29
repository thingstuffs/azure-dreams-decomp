#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800C9B44_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
M2C_UNK func_800C9C94();     /* extern */
M2C_UNK func_800C9DB8();     


/* extern */

/* Advance motion and handle reaching the position limit. */
void func_800C9B44(Rec_func_800C9B44_arg0 *state, EntityRec *motion, M2C_UNK context) {
    u16 remaining_count;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (func_800C2AE8(motion) < motion->z.w.i) {
        motion->z.w.i = func_800C2AE8(motion);
        remaining_count = state->unk_90 - 1;
        state->unk_90 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            motion->flags14 = 0;
            func_800C9DB8(state, motion, context);
            return;
        }
        func_800C9C94(state, motion, context);
        return;
    }
    func_80095388(motion);
}
