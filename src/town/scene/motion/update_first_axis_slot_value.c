#include "town/scene/collision.h"

/* Apply the Y response, increment its face count, and retain the other collider. */
void update_first_axis_slot_value(ColliderView *collider, ObjectPosition *position, CollisionScratch *entry)
{
    int adjusted_value;
    if (entry->face_y == 0) {
        adjusted_value = position->y.v - entry->y_near;
        position->velocity_y = 0;
        position->y.v = adjusted_value;
    }
    collider->pending_flags[entry->axis_y] = (unsigned char)(collider->pending_flags[entry->axis_y] + 1);
    collider->slots[entry->axis_y] = entry->other;
}
