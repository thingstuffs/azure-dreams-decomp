#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"

typedef struct S_8017169C_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8017169C_0;   /* arg3 in advance_actor_path_and_facing */

typedef struct S_8017169C_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_8017169C_2;   /* arg0 in advance_actor_path_and_facing */

   /* (u8 *)arg3 + ((S_8017169C_0 *)arg3)->unk_8A.s in advance_actor_path_and_facing */

extern s32 select_sprite_entry();
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s16 get_rounded_facing_and_rounding_flag();

extern u8 kewne_direction_frames[];

/* Advance the actor along its path and update its facing and movement timing. */
void advance_actor_path_and_facing(void *motion, s32 unused, SpriteFrameState *actor, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 tile_mask;

    if (((S_8017169C_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((S_8017169C_0 *)path_state)->unk_71.u <= ((S_8017169C_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = *(u8 **)&actor->frameTable;
    if (direction_table != kewne_direction_frames) {
        (actor->frameTable) = kewne_direction_frames;
        select_sprite_entry(
            actor,
            kewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017169C_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = actor->tile_x;
    old_y = actor->tile_y;
    tile_mask = 0x3000;
    if (((S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    actor->tile_x =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_8017169C_0 *)path_state)->unk_8A.s))->path_x;
    actor->tile_y =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_8017169C_0 *)path_state)->unk_8A.s))->path_y;
    ((S_8017169C_0 *)path_state)->unk_8A.u++;

    new_x = actor->tile_x;
    new_y = actor->tile_y;
    tile_mask = 0x3000;
    if (((S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);

    ((S_8017169C_0 *)path_state)->unk_2A = get_rounded_facing_and_rounding_flag(
        old_x, old_y, actor->tile_x, actor->tile_y,
        (u8 *)motion + 0x98);
    ((S_8017169C_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((S_8017169C_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((S_8017169C_2 *)motion)->unk_96 = 0;
        return;
    }

    ((S_8017169C_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_8017169C_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((S_8017169C_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}
