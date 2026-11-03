#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "town/person/position.h"
#include "town/player/position.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    u8 pad_00[0xA];
    u16 count;
    u8 pad_0C[0x2A];
    s16 target_x;
    s16 target_y;
} Work;

typedef struct {
    s32 x;
    s32 y;
    u16 pad_08;
    u16 angle;
} Position;


/* Advance the position toward its target and update its angle. */
void advance_player_position_and_angle(void *work_data, ObjectPosition *position_data, SpriteFrameState *sprite) {
    ObjectPosition *pos;
    Work *work;
    u16 steps_left;
    s32 remaining;

    work = work_data;
    pos = position_data;
    steps_left = work->count - 1;
    work->count = steps_left;
    remaining = (s16)steps_left;
    if (remaining <= 0) {
        pos->x.v = work->target_x << 16;
        pos->y.v = work->target_y << 16;
        initialize_record_with_handler_table(work, (pos), sprite);
    } else {
        s32 x;
        s32 y;

        x = pos->x.v;
        pos->x.v = x +
            ((work->target_x << 16) - x) / remaining;
        y = pos->y.v;
        pos->y.v = y +
            ((work->target_y << 16) - y) / (s16)work->count;
    }
    pos->z.unsigned_parts.integer = query_lowered_transform_position(pos);
}
