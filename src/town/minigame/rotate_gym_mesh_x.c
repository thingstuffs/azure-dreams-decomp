#include "shared/sprite_frame_state.h"
#include "town/minigame/object.h"
#include "common.h"
#include "shared/entity.h"

/* Rotate the gym mesh about its X axis. */
void rotate_gym_mesh_x(GymMeshWork *work, ObjectPosition *position, LitMeshSprite *sprite) {
    sprite->rotation[0] -= 0x20;
}
