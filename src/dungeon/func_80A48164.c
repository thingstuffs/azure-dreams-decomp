#include "modules/dungeon_resource06_slot0.h"

void update_actor_object_motion(void *motion, void *unused, void *actor, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 tile_mask;

    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_71.u <= ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = ((R06_80171964_S_8017169C_1 *)actor)->unk_2C;
    if (direction_table != ((u8 *)D_8017586C)) {
        (*(u8 * *)((u8 *)actor + 0x2C)) = ((u8 *)D_8017586C);
        select_sprite_entry(
            actor,
            ((u8 *)D_8017586C)[((g_game_work.view.viewAngle + ((R06_80171964_S_8017169C_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = ((R06_80171964_S_8017169C_1 *)actor)->unk_24;
    old_y = ((R06_80171964_S_8017169C_1 *)actor)->unk_25;
    tile_mask = 0x3000;
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    ((R06_80171964_S_8017169C_1 *)actor)->unk_24 =
        ((R06_80171964_S_8017169C_3 *)((u8 *)path_state + ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s))->unk_74;
    ((R06_80171964_S_8017169C_1 *)actor)->unk_25 =
        ((R06_80171964_S_8017169C_3 *)((u8 *)path_state + ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.s))->unk_7C;
    ((R06_80171964_S_8017169C_0 *)path_state)->unk_8A.u++;

    new_x = ((R06_80171964_S_8017169C_1 *)actor)->unk_24;
    new_y = ((R06_80171964_S_8017169C_1 *)actor)->unk_25;
    tile_mask = 0x3000;
    if (((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.s & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);

    ((R06_80171964_S_8017169C_0 *)path_state)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, ((R06_80171964_S_8017169C_1 *)actor)->unk_24, ((R06_80171964_S_8017169C_1 *)actor)->unk_25,
        (u8 *)motion + 0x98));
    ((R06_80171964_S_8017169C_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((R06_80171964_S_8017169C_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 0;
        return;
    }

    ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((R06_80171964_S_8017169C_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((R06_80171964_S_8017169C_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}
