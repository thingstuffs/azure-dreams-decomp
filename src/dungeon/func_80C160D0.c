#include "modules/dungeon_resource17_slot0.h"

void advance_entity_along_path_2(void *motion, s32 unused, void *entity, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;

    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.u <= ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = ((SpriteTableView *)entity)->unk_2C;
    if (direction_table != ((u8 *)D_80174494) && direction_table != ((u8 *)D_8017449C)) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = ((u8 *)D_8017449C);
        select_sprite_entry(
            entity,
            ((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)motion)->unk_A8 = 0;
    }

    old_x = ((SpriteTableView *)entity)->unk_24;
    old_y = ((SpriteTableView *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

    ((SpriteTableView *)entity)->unk_24 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s))->unk_74;
    ((SpriteTableView *)entity)->unk_25 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s))->unk_7C;
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.u++;

    new_x = ((SpriteTableView *)entity)->unk_24;
    new_y = ((SpriteTableView *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, occupancy_mask);

    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, ((SpriteTableView *)entity)->unk_24, ((SpriteTableView *)entity)->unk_25,
        (u8 *)motion + 0x98));
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 0;
        return;
    }

    ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 8;
    {
        s32 step_count = ((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 8 / step_count;
        }
    }
}
