#include "town/scene/collision.h"

/* Apply the Z response, increment its face count, and retain the other collider. */
void update_second_axis_slot_value(ColliderView *collider, ObjectPosition *position, CollisionScratch *entry)
{
    int adjusted_value;
    if (entry->face_z == 0) {
        adjusted_value = position->z.v - entry->z_near;
        position->velocity_z = 0;
        position->z.v = adjusted_value;
    }
    collider->pending_flags[entry->axis_z] = (unsigned char)(collider->pending_flags[entry->axis_z] + 1);
    collider->slots[entry->axis_z] = entry->other;
}
