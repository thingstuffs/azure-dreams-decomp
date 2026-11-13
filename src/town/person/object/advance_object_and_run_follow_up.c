#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/person/object.h"
#include "town/player.h"

s32 func_800CE04C(s32, s32, s32);


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void advance_object_and_run_follow_up(TownObjectRecord *object, EntityRec *motion, s32 context) {
    object->heading = (u16) (((u16)object->heading) + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_vertical_gravity(motion);
    if (motion->flags14 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
