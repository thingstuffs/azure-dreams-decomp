#include "common.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Moves the position toward the object's target over the remaining steps, then lowers its height by 0x40
 * and clamps it with get_clamped_transform_coordinate. */
void move_position_toward_target(void *work_data, void *position_data, void *completion_arg) {
    ObjectPosition *pos;
    TownObjectRecord *work;
    u16 remaining_count;
    s32 remaining;

    work = work_data;
    pos = position_data;
    remaining_count = work->timer - 1;
    work->timer = remaining_count;
    remaining = (s16)remaining_count;
    if (remaining <= 0) {
        pos->x.v = work->target_x << 16;
        pos->y.v = work->target_y << 16;
        apply_object_setup_and_update(work, pos, completion_arg);
    } else {
        {
            s32 current_x;

            current_x = pos->x.v;
            pos->x.v = current_x +
                ((work->target_x << 16) - current_x) / remaining;
        }
        {
            s32 current_y;

            current_y = pos->y.v;
            *&pos->y.v = current_y +
                ((work->target_y << 16) - current_y) / (s16)work->timer;
        }
    }

    {
        u16 height;

        height = *&pos->z.w.i;
        pos->z.w.i = height - 0x40;
    }
    pos->z.w.i = get_clamped_transform_coordinate(pos);
}
