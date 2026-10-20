#include "modules/dungeon_dungeon_setup.h"

void reset_dungeon_runtime_state(void) {
    u8 *init_flag_page;
    s16 *progress_stats;
    s32 *reset_values;

    bzero(((s32 *)D_800E3548), 0x100);
    bzero(&D_800E36C8, 0x300);
    g_dungeon_status.activity_counts.parts.pending_movement_count = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count = 0;
    g_dungeon_status.trap_counts.parts.pending_trap_count = 0;
    g_dungeon_status.active_actor = 0;
    g_dungeon_status.pending_display_owner = 0;
    ((Rec_D_80083460 *)(&g_dungeon_status.turn_scale))->unk_00 = 0x100;
    g_dungeon_status.flags = 0;
    g_dungeon_status.monster_count = 0;
    g_dungeon_status.movement_frames_left = 0;
    D_800DCE68 = 0;
    D_800E3E40 = 0;
    D_800E296C = 0;
    D_800E3CCC = 0;
    D_800E3CCE = 0;
    D_800DCF4F = 0;
    D_80080A90 = &D_8014A000;
    D_800E3D70 = 0;
    reset_values = &D_800E3D70;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_04 = 0;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_08 = 0;
    D_800DCF58 = 1;
    D_800DCF5B = 0;
    if (D_80082E6B != 5) {
        progress_stats = D_80081468;
        if (progress_stats[2] >= 0x64) {
            progress_stats[2] = 0x63;
        }
        if ((u32) D_80012D60 < (u32) progress_stats[2]) {
            D_80012D60 = (s32) progress_stats[2];
        }
    }
    init_flag_page = (u8 *)0x800E0000;
    if (((dungeon_setup_8028325C_S_8001625C_3 *)((u8 *)init_flag_page - 0x30B2))->unk_00 == 0) {
        file_load_com(&D_80080AE0);
        file_load_com(&D_80080AE8);
        file_load_com(&D_80080E18);
        file_load_com(&D_80080E20);
        file_load_com(&D_80080EE8);
        file_load_com(&D_80080E30);
        D_80080A80 = func_80048D00();
        ((dungeon_setup_8028325C_S_8001625C_3 *)((u8 *)init_flag_page - 0x30B2))->unk_00 = 1;
    }
}

/* MECHANISM: Named D_80083460 and D_80081468 bases reproduce the retail held-address forms.
   D_800E3D70 and D_80012D60 use their symbol addresses without duplicated byte displacements.
   Holding the 0x800E0000 page in s0 removes one addiu and closes the branch-displacement cascade. */
