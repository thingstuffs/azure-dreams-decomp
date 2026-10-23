#include "common.h"
#include "dungeon/actor/motion.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern u8 actor_action_resume_address[];

/* Runs terrain-tile interpolation and installs actor_action_resume_address when it completes. */
void run_terrain_tile_interpolation(void *owner_in, ObjectPosition *motion, MovingTile *tile, void *height) {
    CallbackOwner *owner = owner_in;
    if (interpolate_actor_to_terrain_tile(owner_in, motion, tile, height) != 0) {
        owner->callback = actor_action_resume_address;
    }
}
