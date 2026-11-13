#include "common.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/person/position.h"
#include "town/person/motion.h"
#include "town/player.h"

#include "town/person/object_setup.h"
void func_800CDE9C(void *object, EntityRec *unusedArg, void *initValue);     /* extern */
s32 func_800CDFF8();

/* Update spin and vertical motion, then handle ground contact and remaining bounces. */
void update_spin_vertical_motion_and_bounces(TownObjectRecord *entity, EntityRec *motion, void *context) {
    s16 remaining_bounces;

    entity->heading = (u16) (((u16)entity->heading) + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        remaining_bounces = entity->unk_90 - 1;
        entity->unk_90 = remaining_bounces;
        if (remaining_bounces <= 0) {
            motion->flags14 = 0;
            entity->heading = (u16) entity->unk_6E;
            func_800CDE9C(entity, motion, context);
            return;
        }
        if (select_object_setup_path(entity, motion, context) == 0) {
            func_800CDFF8(entity, motion, context);
            return;
        }
    } else {
        add_vertical_gravity(motion);
    }
}
