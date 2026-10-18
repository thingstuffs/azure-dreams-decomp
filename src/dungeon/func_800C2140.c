#include "common.h"
#include "shared/entity_objects.h"

extern u16 D_800E58F8[];
extern s32 select_nearby_target_and_initialize_slot(s32 slot_id, void *target, s32 target_id, s32 slot_value);

/* Sets up the object at the supplied position if both planar distances are at most 192. */
void setup_object_within_planar_range(s32 object, s32 x, s32 y, s32 height, s32 mode, s32 settings)
{
    s32 saved_mode;

    saved_mode = mode;
    mode = D_80083780.x.w.i - x;
    if (mode < 0) {
        mode = -mode;
    }
    if (mode < 193) {
        mode = D_80083780.y.w.i - y;
        if (mode < 0) {
            mode = -mode;
        }
        if (mode < 193) {
            u16 *position = D_800E58F8;

            position[1] = x;
            position[3] = y;
            position[5] = height;
            select_nearby_target_and_initialize_slot((void *)object, position, (s16)saved_mode, settings);
        }
    }
}
