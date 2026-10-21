#include "common.h"
#include "shared/entity_objects.h"

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s32 unk8;
} DungeonPoint;


/* Return the direction from the global point to the target, or 9 if coincident. */
s32 get_player_relative_point_octant(DungeonPoint *target)
{

    if (view_reference_entity.x.w.i == target->x &&view_reference_entity.y.w.i == target->y) {
        return 9;
    }

    if (view_reference_entity.x.w.i < target->x) {
        if (view_reference_entity.y.w.i < target->y) {
            return 1;
        }
        if (target->y < view_reference_entity.y.w.i) {
            return 7;
        }
        return 0;
    }

    if (target->x < view_reference_entity.x.w.i) {
        if (view_reference_entity.y.w.i < target->y) {
            return 3;
        }
        if (target->y < view_reference_entity.y.w.i) {
            return 5;
        }
        return 4;
    }

    if (view_reference_entity.y.w.i < target->y) {
        return 2;
    }
    if (target->y < view_reference_entity.y.w.i) {
        return 6;
    }
    return 0;
}
