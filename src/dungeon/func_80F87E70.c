#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "shared/sprite_frame_state.h"

typedef struct S_80171670_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171670_0;   /* arg3 in advance_bank_actor_path */

   /* arg2 in advance_bank_actor_path */

typedef struct S_80171670_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x5];
    s16 unk_A0;
} S_80171670_2;   /* arg0 in advance_bank_actor_path */

   /* (u8 *)arg3 + ((S_80171670_0 *)arg3)->unk_8A.s in advance_bank_actor_path */



/* Advance the entity along its stored path and update its movement state. */
void advance_bank_actor_path(void *motion, s32 unused, void *entity, void *path_state)
{
    SpriteTableView *entity_view = entity;
    u8 *anim_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 cell_mask;

    if (((S_80171670_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171670_0 *)path_state)->unk_71.u <= ((S_80171670_0 *)path_state)->unk_8A.s) {
        return;
    }

    anim_table = entity_view->unk_2C;
    if (anim_table != D_80174AD4) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80174AD4;
        func_80047784(
            entity,
            D_80174AD4[((g_game_work.view.viewAngle + ((S_80171670_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80171670_2 *)motion)->unk_A0 = 0;
    }

    old_x = entity_view->unk_24;
    old_y = entity_view->unk_25;
    cell_mask = 0x3000;
    if (((S_80171670_0 *)path_state)->unk_1C.s & 0x2000) {
        cell_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, cell_mask);

    entity_view->unk_24 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_80171670_0 *)path_state)->unk_8A.s))->unk_74;
    entity_view->unk_25 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_80171670_0 *)path_state)->unk_8A.s))->unk_7C;
    ((S_80171670_0 *)path_state)->unk_8A.u++;

    new_x = entity_view->unk_24;
    new_y = entity_view->unk_25;
    cell_mask = 0x3000;
    if (((S_80171670_0 *)path_state)->unk_1C.s & 0x2000) {
        cell_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, cell_mask);

    ((S_80171670_0 *)path_state)->unk_2A = (s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, entity_view->unk_24, entity_view->unk_25,
        (u8 *)motion + 0x98);
    ((S_80171670_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((S_80171670_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((S_80171670_2 *)motion)->unk_96 = 0;
        return;
    }

    ((S_80171670_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_80171670_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((S_80171670_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}

