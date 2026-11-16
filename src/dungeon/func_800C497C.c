#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800C9F34_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"
#include "dungeon/item.h"

   /* Advances to the next path coordinate and updates movement state and timing. */
void advance_actor_along_path_points(ActorRecord *motion, s32 unused, void *position, ActorRecord *path)
{
    s32 step_count;
    s32 old_x;
    s32 old_y;

    if (((s8)path->movement_queue_state) <= 0) {
        return;
    }
    if (path->movement_queue_state <= path->unk_8A) {
        return;
    }

    old_x = ((MovingTile *)position)->tile_x;
    old_y = ((MovingTile *)position)->tile_y;
    ((MovingTile *)position)->tile_x =
        ((ActorStatusBytesView *)((u8 *)path + path->unk_8A))->path_x;
    ((MovingTile *)position)->tile_y =
        ((ActorStatusBytesView *)((u8 *)path + path->unk_8A))->path_y;
    path->unk_8A = path->unk_8A + 1;

    path->facing =
        get_rounded_facing_and_rounding_flag(old_x, old_y, ((MovingTile *)position)->tile_x,
                      ((MovingTile *)position)->tile_y, &motion->action_state_flags);
    path->flags1C |= 0x40000000;
    motion->action_id = 0xF;
    motion->unk_8C.word = 0;

    if (g_dungeon_status.flags & 0x80) {
        motion->action_timer = 0;
        return;
    }

    motion->action_timer = 8;
    step_count = path->movement_queue_state;
    if (step_count > 0) {
        motion->action_timer = 8 / step_count;
    }
}
