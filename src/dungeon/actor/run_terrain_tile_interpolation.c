#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;

/* Runs terrain-tile interpolation and installs update_actor_facing_animation when it completes. */
void run_terrain_tile_interpolation(void *owner_in, ObjectPosition *motion, MovingTile *tile, void *height) {
    CallbackOwner *owner = owner_in;
    if (interpolate_actor_to_terrain_tile(owner_in, motion, tile, height) != 0) {
        owner->callback = update_actor_facing_animation;
    }
}
