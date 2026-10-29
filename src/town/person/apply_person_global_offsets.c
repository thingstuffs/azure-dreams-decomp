#include "common.h"
#include "town/player/position.h"

extern s16 town_motion_x_step;
extern s16 town_motion_y_step;

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} Object;

/* Applies the global offsets scaled by 64 to the object and updates it. */
void apply_person_global_offsets(void *unused_first, void *unused_second, Object *object) {
    object->x += town_motion_x_step << 6;
    object->y += town_motion_y_step << 6;
    add_motion_deltas_to_position(object);
}
