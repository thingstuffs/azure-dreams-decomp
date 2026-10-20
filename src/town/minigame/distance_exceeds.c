#include "common.h"

#include "shared/entity_objects.h"

static __inline__ s16 distance_exceeds(s32 limit, s32 distance) {
    return limit < __builtin_abs(distance);
}

typedef struct S0 {
    char pad0[0x68];
    s16 f68;
    char pad6A[2];
    s16 f6C;
} S0;

typedef struct S1 {
    char pad0[0x1A];
    u16 f1A;
} S1;

extern s32 service_script_controller(s32, s32 *, S1 *);
extern s32 check_transform_identifier_and_hook(S0 *);
extern void SD_Call(s32);
static s32 state;


/* Updates the object state, position, and timed target adjustments. */
void update_object_state_position(S0 *self, s32 *position, S1 *target) {
    register s32 state;
    S0 *object = self;
    s32 y_limit;
    s32 next_value;
    s32 next_value_2;
    s32 base_y;

    {
        s32 countdown;

        countdown = (u16)object->f6C;
        base_y = position[1];
        state = object->f68;
        countdown--;
        object->f6C = countdown;
    }
    next_value_2 = 0x800000;
    y_limit = base_y + next_value_2;
    switch (state) {
    case 0:
    case 3:
    {
        register s32 threshold;
        register s32 x_distance;
        s32 target_x;

        x_distance = D_80083780.x.v;
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
        next_value = (u16)object->f68;
        threshold = 32;
        object->f6C = threshold;
        object->f68 = next_value + 1;
        return;
    }

    case 1:
    {
        s32 below_limit;

        below_limit = D_80083780.y.v < y_limit;
        if (below_limit != 0) {
            D_80083780.y.v += 0x40000;
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
        object->f68 = (object->f68 + 1) % 6;
        return;

    case 4:
        next_value = target->f1A + 32;
        break;
    default:
        return;
    }
    target->f1A = next_value;
    if (object->f6C > 0) {
        return;
    }
    next_value = (u16)object->f68;
    object->f68 = next_value + 1;
    return;
}

