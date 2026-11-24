#include "dungeon/actor/motion.h"
#include "dungeon/monster/kid.h"

void resume_kid_behavior_after_interpolation(ActorRecord *actor, ObjectPosition *motion, MovingTile *tile, ActorRecord *height)
{
    if (interpolate_actor_to_terrain_tile(actor, motion, tile, height)) {
        actor->unk_8C.address = update_kid_behavior;
    }
}
