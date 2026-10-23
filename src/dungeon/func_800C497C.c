#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800C9F34_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"


extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);


typedef struct S_800CA0DC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800CA0DC_0;   /* arg3 in advance_actor_along_path_points */

   /* Advances to the next path coordinate and updates movement state and timing. */
void advance_actor_along_path_points(void *motion, s32 unused, void *position, void *path)
{
    s32 step_count;
    s32 old_x;
    s32 old_y;

    if (((S_800CA0DC_0 *)path)->unk_71.s <= 0) {
        return;
    }
    if (((S_800CA0DC_0 *)path)->unk_71.u <= ((S_800CA0DC_0 *)path)->unk_8A.s) {
        return;
    }

    old_x = ((MovingTile *)position)->unk_24;
    old_y = ((MovingTile *)position)->unk_25;
    ((MovingTile *)position)->unk_24 =
        ((ActorStatusBytesView *)((u8 *)path + ((S_800CA0DC_0 *)path)->unk_8A.s))->unk_74;
    ((MovingTile *)position)->unk_25 =
        ((ActorStatusBytesView *)((u8 *)path + ((S_800CA0DC_0 *)path)->unk_8A.s))->unk_7C;
    ((S_800CA0DC_0 *)path)->unk_8A.u++;

    ((S_800CA0DC_0 *)path)->unk_2A =
        get_rounded_facing_and_rounding_flag(old_x, old_y, ((MovingTile *)position)->unk_24,
                      ((MovingTile *)position)->unk_25, (u8 *)motion + 0x98);
    ((S_800CA0DC_0 *)path)->unk_1C |= 0x40000000;
    ((Rec_func_800C9F34_arg0 *)motion)->unk_9A.as_u8 = 0xF;
    (*(s32 *)((u8 *)motion + (0x8C))) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 0;
        return;
    }

    ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 8;
    step_count = ((S_800CA0DC_0 *)path)->unk_71.u;
    if (step_count > 0) {
        ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 8 / step_count;
    }
}
