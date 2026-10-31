#include "common.h"

typedef struct {
    u8 pad_00[0x6C];
    u16 count;
    u8 pad_6E[0x1A];
    s16 target_x;
    s16 target_y;
} Work;

typedef struct {
    s32 x;
    s32 y;
    u16 pad_08;
    u16 angle;
} Position;

extern s32 get_clamped_transform_coordinate(void *object);
#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Moves the position toward its target over the remaining steps and updates its angle. */
void move_position_toward_target(void *work_data, void *position_data, void *completion_arg) {
    Position *pos;
    Work *work;
    u16 remaining_count;
    s32 remaining;

    work = work_data;
    pos = position_data;
    remaining_count = work->count - 1;
    work->count = remaining_count;
    remaining = (s16)remaining_count;
    if (remaining <= 0) {
        pos->x = work->target_x << 16;
        pos->y = work->target_y << 16;
        apply_object_setup_and_update(work, pos, completion_arg);
    } else {
        {
            s32 current_x;

            current_x = pos->x;
            pos->x = current_x +
                ((work->target_x << 16) - current_x) / remaining;
        }
        {
            s32 current_y;

            current_y = pos->y;
            *&pos->y = current_y +
                ((work->target_y << 16) - current_y) / (s16)work->count;
        }
    }

    {
        u16 angle;

        angle = *&pos->angle;
        pos->angle = angle - 0x40;
    }
    pos->angle = get_clamped_transform_coordinate(pos);
}
