#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 interpolate_actor_to_terrain_tile(void);
extern u8 actor_action_resume_address[];

/* Runs terrain-tile interpolation and installs actor_action_resume_address when it completes. */
void run_terrain_tile_interpolation(CallbackOwner *owner) {
    if (interpolate_actor_to_terrain_tile() != 0) {
        owner->callback = actor_action_resume_address;
    }
}
