#include "modules/dungeon_ovl_e0365c.h"

void update_actor_spell_action(void *arg0, E_80172A58_S_80172A58_6 *arg1, E_80172A58_S_80172A58_5 *arg2, void *arg3) {
    s32 result;
    s32 next_ticks;
    s16 use_player_target;
    s8 unused_result_byte;
    s8 unused_state_byte;
    u16 remaining_ticks;
    u8 *action_entry;
    u8 phase;
    E_80172A58_S_80172A58_4 *target_position;
    void *target_link;

    phase = ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B;
    use_player_target = 0;
    switch (phase) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (((E_80172A58_S_80172A58_1 *)arg3)->unk_1C & 0x2000) {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 7: use_player_target=1;
            case 3: action_entry=(u8 *)arg3+0xE; break;
            case 6: use_player_target=1;
            case 2: action_entry=(u8 *)arg3+0xB; break;
            case 5: use_player_target=1;
            case 1: action_entry=(u8 *)arg3+8; break;
            default: action_entry=0; break;
            }
        } else {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 3: action_entry=(u8 *)arg3+0xE; break;
            case 2: action_entry=(u8 *)arg3+0xB; break;
            case 1: action_entry=(u8 *)arg3+8; break;
            default: action_entry=0; break;
            }
        }
        if (*action_entry != 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_98 = (u16) (((E_80172A58_S_80172A58_0 *)arg0)->unk_98 & 0xFF7F);
            if (use_player_target != 0) {
                target_link = D_800814A8;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = target_link;
                    target_position = ((E_80172A58_S_80172A58_3_pre *)target_link)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) target_position->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) target_position->unk_25;
            } else if (((E_80172A58_S_80172A58_2 *)(((*action_entry * 0x14) + D_8006DE24)))->unk_12 == 2) {
                target_link = ((E_80172A58_S_80172A58_1 *)arg3)->unk_60;
                if (target_link != NULL) {
                    target_position = ((E_80172A58_S_80172A58_3_pre *)target_link)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) target_position->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) target_position->unk_25;
                }
            } else {
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = scan_monster_along_heading(arg3, arg2->unk_24, arg2->unk_25, ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A, 0x10);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_72);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_73);
            }
            if (create_actor_spell_effect(arg3, action_entry, use_player_target, arg0 + 0x98) != 0) {
                create_actor_linked_effect(arg3);
                ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B = (u8) (((E_80172A58_S_80172A58_0 *)arg0)->unk_9B + 1);
                return;
            }
            return;
        }
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        set_record_integer_tile_center(arg1, arg2->unk_24, arg2->unk_25);
        g_dungeon_status.unk_0C = 0;
        ((E_80172A58_S_80172A58_7 *)D_800814A8)->unk_A6 = (u16) (((E_80172A58_S_80172A58_7 *)D_800814A8)->unk_A6 - 1);
        advance_status_timers(arg3);
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_6D = (u8) (((E_80172A58_S_80172A58_1 *)arg3)->unk_6D - 1);
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = update_actor_behavior_facing_and_animation_2;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = 0;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = 0;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_46 = (u16) (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (get_cd_command_queue_depth() != 0) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            return;
        }
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B = (u8) (((E_80172A58_S_80172A58_0 *)arg0)->unk_9B + 1);
    case 2:                                         /* switch 1 */
        if (((arg2->unk_04 == 3) && (arg2->unk_14 & 0x1000)) || (arg2->unk_14 & 0xE000)) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = 1U;
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_98 = (u16) (((E_80172A58_S_80172A58_0 *)arg0)->unk_98 | 0x80);
        }
        remaining_ticks = ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 - 1;
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = 0U;
            arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        }
        if (arg2->unk_14 & 0xE000) {
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            set_record_integer_tile_center(arg1, arg2->unk_24, arg2->unk_25);
            if (arg2->unk_2C != D_80174520) {
                arg2->unk_2C = D_80174520;
                select_sprite_entry(arg2, *((((s32) (g_game_work.view.viewAngle + ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_80174520), 0);
            }
            if (g_dungeon_status.unk_0C == 0) {
                g_dungeon_status.unk_0A = (u16) (g_dungeon_status.unk_0A - 1);
                ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = update_actor_behavior_facing_and_animation_2;
                advance_status_timers(arg3);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = 0;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = 0;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_6D = (u8) (((E_80172A58_S_80172A58_1 *)arg3)->unk_6D - 1);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_46 = (u16) (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
                play_sound_if_enabled(0xB4);
            }
        }
        break;
    }
}
