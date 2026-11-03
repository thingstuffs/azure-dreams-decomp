#include "common.h"
#include "shared/entity.h"
#include "town/player.h"

extern s32 town_collision_motion[];

/* Clears slot 3 and copies the supplied value into slot 0. */
void clear_slot_n_3_copies_slot_n_0(ObjectPosition *position) {
    town_collision_motion[3] = 0;
    town_collision_motion[0] = position->x.v;
}
