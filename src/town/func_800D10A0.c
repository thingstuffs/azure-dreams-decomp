#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
void func_800C4174();     /* extern */
extern M2C_UNK D_800CE8CC;


/* Advance vertical motion, clamp at the landing height, and bounce or finish. */
void func_800CE800(Rec_func_80094268_arg0 *actor, EntityRec *motion, s32 context) {
    u16 bounces_left;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (func_800C2AE8(motion) < motion->z.w.i) {
        motion->z.w.i = func_800C2AE8(motion);
        bounces_left = actor->unk_90.as_u16 - 1;
        actor->unk_90.as_u16 = bounces_left;
        if ((bounces_left << 0x10) <= 0) {
            motion->flags14 = 0;
            func_800C4174(actor, motion, context);
            return;
        }
        motion->flags14 = 0xFFF60000;
        actor->unk_54 = &D_800CE8CC;
        return;
    }
    func_80095388(motion);
}
