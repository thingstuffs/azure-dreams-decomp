#include "town/person.h"
#include "engine/resource.h"
#include "sdk/libc.h"
#include "shared/object_index_slots.h"
#include "town/person/object_setup.h"

/* advance_reaction_motion_to_limit declares this with an s16 result; the two
 * callers disagree, so the declaration stays with each caller. */
extern s32 query_lowered_transform_position(ObjectPosition *);

/* Start movement toward the object's target, or place it immediately for speed -128. */
void start_person_target_move(PersonObject *object, ObjectPosition *position, s8 *output) {
    ObjectIndexSlot *slots;
    s32 distance;
    s32 timer;
    s8 speed;
    s32 magnitude;

    slots = object_index_slots;
    slots[object->slot].unk_00 = 0;
    object->handler = move_position_toward_target;
    distance = runtime_estimate_vector_length((object->target_x << 16) - position->x.v,
                           (object->target_y << 16) - position->y.v);
    timer = distance / 0x20000;
    object->timer = timer;
    speed = slots[object->slot].unk_02;
    if (speed == -0x80) {
        position->x.v = object->target_x << 16;
        position->y.v = object->target_y << 16;
        position->z.w.i -= 0x40;
        position->z.w.i = query_lowered_transform_position(position);
        apply_object_setup_and_update(object, position, output);
    } else if (speed > 0) {
        object->timer = (timer << 4) / (speed + 0x10);
    } else if (speed < 0) {
        magnitude = abs(speed);
        object->timer = timer * (magnitude + 0x10) / 16;
    }
}
