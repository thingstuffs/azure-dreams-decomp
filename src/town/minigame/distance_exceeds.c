/* Updates object motion states and timed target adjustments using distance checks. */
#include "common.h"

#include "shared/entity_objects.h"
#include "slus.h"
#include "town/minigame.h"
#include "town/minigame/object.h"
#include "town/person.h"

/* Returns whether the absolute signed distance exceeds the supplied limit. */
static __inline__ s16 distance_exceeds(s32 limit, s32 distance) {
    return limit < __builtin_abs(distance);
}

typedef struct S1 {
    char pad0[0x1A];
    u16 f1A;
} S1;

extern s32 service_script_controller(s32, s32 *, S1 *); /* Unprototyped: retail call passes more arguments than the callee reads */
static s32 state;


/* Updates the object state, position, and timed target adjustments. */
void update_object_state_position(ObjectStatePositionObject *self, s32 *position, S1 *target) {
    register s32 phase;
    ObjectStatePositionObject *object = self;
    s32 y_limit;
    s32 next_value;
    s32 next_value_2;
    s32 base_y;

    {
        s32 countdown;

        countdown = (u16)object->countdown;
        base_y = position[1];
        phase = object->phase;
        countdown--;
        object->countdown = countdown;
    }
    next_value_2 = 0x800000;
    y_limit = base_y + next_value_2;
    switch (phase) {
    case 0:
    case 3:
    {
        register s32 threshold;
        register s32 x_distance;
        s32 target_x;

        x_distance = view_reference_entity.x.v;
        target_x = position[0];
        x_distance -= target_x;
        threshold = 0x3FFFFF;

        threshold = distance_exceeds(threshold, x_distance);
        if (threshold != 0) {
            return;
        }
        if (service_script_controller(target_x, position, target) == 0) {
            return;
        }
        if (check_transform_identifier_and_hook(object) == 0) {
            return;
        }
        SD_Call(0x50B);
        next_value = (u16)object->phase;
        threshold = 32;
        object->countdown = threshold;
        object->phase = next_value + 1;
        return;
    }

    case 1:
    {
        s32 below_limit;

        below_limit = view_reference_entity.y.v < y_limit;
        if (below_limit != 0) {
            view_reference_entity.y.v += 0x40000;
        }
        next_value = target->f1A - 32;
        break;
    }

    case 2:
    case 5:
        if (service_script_controller((s32)self, position, target) != 0) {
            if (check_transform_identifier_and_hook(object) != 0) {
                return;
            }
        }
        object->phase = (object->phase + 1) % 6;
        return;

    case 4:
        next_value = target->f1A + 32;
        break;
    default:
        return;
    }
    target->f1A = next_value;
    if (object->countdown > 0) {
        return;
    }
    next_value = (u16)object->phase;
    object->phase = next_value + 1;
    return;
}

