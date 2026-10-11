#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

extern void func_80095388(EntityRec *record);
extern s16 func_800C2AE8(void *position);
s32 func_800C30E0();         /* extern */
s32 func_800CDE9C();     /* extern */
s32 func_800CDFF8();

/* extern */

/* Update spin and vertical motion, then handle ground contact and remaining bounces. */
void func_800CDCA8(Rec_func_80094268_arg0 *entity, EntityRec *motion, s32 context) {
    s16 remaining_bounces;

    entity->unk_72.as_u16 = (u16) (entity->unk_72.as_u16 + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (func_800C2AE8(motion) < motion->z.w.i) {
        motion->z.w.i = func_800C2AE8(motion);
        remaining_bounces = entity->unk_90.as_s16 - 1;
        entity->unk_90.as_s16 = remaining_bounces;
        if (remaining_bounces <= 0) {
            motion->flags14 = 0;
            entity->unk_72.as_u16 = (u16) entity->unk_6E;
            func_800CDE9C(entity, motion, context);
            return;
        }
        if (func_800C30E0(entity, motion, context) == 0) {
            func_800CDFF8(entity, motion, context);
            return;
        }
    } else {
        func_80095388(motion);
    }
}
