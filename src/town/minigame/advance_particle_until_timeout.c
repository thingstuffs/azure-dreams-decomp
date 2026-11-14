#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "town/minigame.h"
#include "town/minigame/brief_random_particle_body.h"

/* Advance the position and flag the record and global state when its timer expires. */
void advance_particle_until_timeout(BriefRandomParticleBody *record_data, ObjectPosition *motion) {
    u16 ticks_left;

    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    ticks_left = record_data->ticks_left - 1;
    record_data->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(record_data)->flags = (u16) (NODE_HEADER(record_data)->flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
