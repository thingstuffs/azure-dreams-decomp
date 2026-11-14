#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800C9F34_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"
#include "dungeon/item.h"

typedef struct S_800CA0DC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    u8 unk_71;
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800CA0DC_0;   /* arg3 in advance_actor_along_path_points */

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
    ((S_800CA0DC_0 *)path)->unk_8A.u++;

    path->facing =
        get_rounded_facing_and_rounding_flag(old_x, old_y, ((MovingTile *)position)->tile_x,
                      ((MovingTile *)position)->tile_y, (u8 *)motion + 0x98);
    path->flags1C |= 0x40000000;
    motion->action_id = 0xF;
    (*(s32 *)((u8 *)motion + (0x8C))) = 0;

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
