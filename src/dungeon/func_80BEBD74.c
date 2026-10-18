#include "modules/dungeon_resource16_slot0.h"

void advance_actor_path_step_and_update_counters(void *motion_state, s32 unused, void *entity, void *path_state)
{
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    u16 hp;
    u16 energy;
    u16 step_index;
    void *path_entry;

    if (((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if ((s32)((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.u <= ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s) {
        return;
    }

    if (((R16_80171574_S_80171FC8_1 *)entity)->unk_2C != ((u8 *)D_8017420C)) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = ((u8 *)D_8017420C);
        func_80047784(entity,
                      ((u8 *)D_8017420C)[((g_game_work.view.viewAngle + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
                      0);
    }

    path_entry = (u8 *)path_state + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s;
    if (((R16_80171574_S_80171FC8_1 *)entity)->unk_24 == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_74 &&
        ((R16_80171574_S_80171FC8_1 *)entity)->unk_25 == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_7C) {
        hp = ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92;
        energy = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88;
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92 = hp + 0x20;
        step_index = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88 = energy - 0x20;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u = step_index + 1;
    } else {
        flags = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C;
        old_x = ((R16_80171574_S_80171FC8_1 *)entity)->unk_24;
        old_y = ((R16_80171574_S_80171FC8_1 *)entity)->unk_25;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        ((R16_80171574_S_80171FC8_1 *)entity)->unk_24 = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_74;
        ((R16_80171574_S_80171FC8_1 *)entity)->unk_25 = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_7C;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u += 1;

        cycle_map_cell_flags(((R16_80171574_S_80171FC8_1 *)entity)->unk_24, ((R16_80171574_S_80171FC8_1 *)entity)->unk_25,
                      (((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A =
            ((s16)get_rounded_facing_and_rounding_flag(old_x, old_y, ((R16_80171574_S_80171FC8_1 *)entity)->unk_24,
                          ((R16_80171574_S_80171FC8_1 *)entity)->unk_25, (u8 *)motion_state + 0x98));
    }

    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_9A = 0xF;
    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_8C = 0;
    (*(s32 *)((u8 *)path_state + 0x1C)) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 0;
        return;
    }

    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 8;
    step_count = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.u;
    if (step_count > 0) {
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 8 / step_count;
    }

    return;
}
