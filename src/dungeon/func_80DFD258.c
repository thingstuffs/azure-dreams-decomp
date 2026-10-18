/* Relink of matched dungeon/func_80DE5258; every changed retail word is a paired relocation. */
#define D_80174520 D_8015C520
#include "modules/dungeon_ovl_e0365c.h"
extern void func_80158E5C(void *, void *, void *, void *);

void func_8015AA58(void *arg0, E_80172A58_S_80172A58_6 *arg1, E_80172A58_S_80172A58_5 *arg2, void *arg3) {
    s32 temp_v0;
    s32 temp_v1_2;
    s16 var_s5;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u8 *var_s0;
    u8 temp_v1;
    E_80172A58_S_80172A58_4 *temp_v1_3;
    void *var_v0;

    temp_v1 = ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B;
    var_s5 = 0;
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (((E_80172A58_S_80172A58_1 *)arg3)->unk_1C & 0x2000) {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 7: var_s5=1;
            case 3: var_s0=(u8 *)arg3+0xE; break;
            case 6: var_s5=1;
            case 2: var_s0=(u8 *)arg3+0xB; break;
            case 5: var_s5=1;
            case 1: var_s0=(u8 *)arg3+8; break;
            default: var_s0=0; break;
            }
        } else {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 3: var_s0=(u8 *)arg3+0xE; break;
            case 2: var_s0=(u8 *)arg3+0xB; break;
            case 1: var_s0=(u8 *)arg3+8; break;
            default: var_s0=0; break;
            }
        }
        if (*var_s0 != 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_98 = (u16) (((E_80172A58_S_80172A58_0 *)arg0)->unk_98 & 0xFF7F);
            if (var_s5 != 0) {
                var_v0 = D_800814A8;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = var_v0;
                    temp_v1_3 = ((E_80172A58_S_80172A58_3_pre *)var_v0)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) temp_v1_3->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) temp_v1_3->unk_25;
            } else if (((E_80172A58_S_80172A58_2 *)(((*var_s0 * 0x14) + D_8006DE24)))->unk_12 == 2) {
                var_v0 = ((E_80172A58_S_80172A58_1 *)arg3)->unk_60;
                if (var_v0 != NULL) {
                    temp_v1_3 = ((E_80172A58_S_80172A58_3_pre *)var_v0)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) temp_v1_3->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) temp_v1_3->unk_25;
                }
            } else {
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = scan_monster_along_heading(arg3, arg2->unk_24, arg2->unk_25, ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A, 0x10);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_72);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_73);
            }
            if (create_actor_spell_effect(arg3, var_s0, var_s5, arg0 + 0x98) != 0) {
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
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = func_80158E5C;
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
        temp_v0_2 = ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 - 1;
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = 0U;
            arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        }
        if (arg2->unk_14 & 0xE000) {
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            set_record_integer_tile_center(arg1, arg2->unk_24, arg2->unk_25);
            if (arg2->unk_2C != D_8015C520) {
                arg2->unk_2C = D_8015C520;
                func_80047784(arg2, *((((s32) (g_game_work.view.viewAngle + ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_8015C520), 0);
            }
            if (g_dungeon_status.unk_0C == 0) {
                g_dungeon_status.unk_0A = (u16) (g_dungeon_status.unk_0A - 1);
                ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = func_80158E5C;
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
