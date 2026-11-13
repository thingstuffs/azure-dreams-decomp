#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "town/person/position.h"
#include "engine/node.h"
#include "town/player.h"
#include "town/scene.h"

#include "town/person.h"
extern s32 D_800D636C[2];


/* Advance motion and handle ground contact or continued movement. */
void step_falling_object(OwnerCallbackObject *entity, ObjectPosition *motion, SpriteFrameState *output)
{
    s32 *velocity;
    u16 contacts_left;

    velocity = D_800D636C;
    motion->x.v += velocity[0];
    motion->y.v += velocity[1];
    motion->z.v += motion->velocity_z;
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        contacts_left = entity->contacts_left.as_u16 - 1;
        entity->contacts_left.as_u16 = contacts_left;
        if ((s16)contacts_left < 0) {
            unlink_node_if_registered(entity);
            initialize_falling_object_sprite(entity, motion, output);
            return;
        }
        load_indexed_state_value(entity, motion, output);
        return;
    }
    add_vertical_gravity(motion);
}
