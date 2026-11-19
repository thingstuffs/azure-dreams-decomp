#include "shared/sprite_frame_state.h"
#include "town/minigame/object.h"
#include "common.h"
#include "town/minigame.h"

/* Rotate the gym mesh about its Y axis. */
void rotate_gym_mesh_y(GymMeshWork *work, ObjectPosition *position, LitMeshSprite *sprite) {
    sprite->rotation[1] += 0x20;
}
