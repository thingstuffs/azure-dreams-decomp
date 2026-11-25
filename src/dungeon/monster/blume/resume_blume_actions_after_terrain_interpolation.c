#include "dungeon/actor/motion.h"
#include "dungeon/monster/blume.h"

void resume_blume_actions_after_terrain_interpolation(ActorRecord *actor, ObjectPosition *motion, MovingTile *tile, ActorRecord *height)
{
    if (interpolate_actor_to_terrain_tile(actor, motion, tile, height)) {
        actor->unk_8C.address = dispatch_blume_actions;
    }
}
