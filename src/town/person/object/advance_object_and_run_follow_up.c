#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/person/object.h"
#include "town/player.h"

void func_800CE04C(TownObjectRecord *, ObjectPosition *, SpriteFrameState *);


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void advance_object_and_run_follow_up(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    object->heading = (u16) (((u16)object->heading) + 0x400);
    motion->z.v += motion->velocity_z;
    add_vertical_gravity(motion);
    if (motion->velocity_z >= 0) {
        func_800CE04C(object, motion, sprite);
    }
}
