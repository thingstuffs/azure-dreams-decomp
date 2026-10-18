#include "modules/dungeon_resource16_slot0.h"

void update_overlay_object_action(void *owner, void *motion, void *actor, void *object_in)
{
    void *object = object_in;
    register s32 is_special;
    u8 *action_data;
    s16 x;
    s32 absolute_x;
    s32 y;
    s32 kind;
    u32 kind_index;
    void *spawn;
    u8 *action_entry;
    u8 *record;
    u8 *action_table;
    u32 action_id;
    s32 state;
    state = ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B;
    is_special = 0;
    switch (state) {
    case 0:
        if (((R16_801725A4_S_801725A4_1 *)object)->unk_1C & 0x2000) {
            kind_index = (((R16_801725A4_S_801725A4_1 *)object)->unk_46 & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                is_special = 1;
            case 2:
                action_data = (u8 *)object + 0xE;
                break;
            case 5:
                is_special = 1;
            case 1:
                action_data = (u8 *)object + 0xB;
                break;
            case 4:
                is_special = 1;
            case 0:
                action_data = (u8 *)object + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            kind = ((R16_801725A4_S_801725A4_1 *)object)->unk_46 & 0x3FFF;
            switch (kind) {
            case 3:
                action_data = (u8 *)object + 0xE;
                break;
            case 2:
                action_data = (u8 *)object + 0xB;
                break;
            case 1:
                action_data = (u8 *)object + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {
            x = ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 & 0xFF7F;
            ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 = x;
            x = is_special;
            if (x) {
                spawn = D_800814A8;
                ((R16_801725A4_S_801725A4_1 *)object)->unk_60 = spawn;
                record = *(u8 **)((u8 *)spawn - 0x14);
                x = record[0x24];
                ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                x = record[0x25];
                ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
            } else {
                action_table = D_8006DE24;
                action_id = *action_data;
                action_entry = action_table + (action_id * 20);
                if (action_entry[0x12] == 2) {
                    spawn = ((R16_801725A4_S_801725A4_1 *)object)->unk_60;
                    if (spawn != 0) {
                        record = *(u8 **)((u8 *)spawn - 0x14);
                        x = record[0x24];
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                        x = record[0x25];
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
                    }
                } else {
                    spawn = scan_monster_along_heading(
                        object,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25),(s16)(((R16_801725A4_S_801725A4_1 *)object)->unk_2A),
                        0x10);
                    ((R16_801725A4_S_801725A4_1 *)object)->unk_60 = spawn;

                    absolute_x = abs(((R16_801725A4_S_801725A4_1 *)object)->unk_72.u);
                    y = abs(((R16_801725A4_S_801725A4_1 *)object)->unk_73.u);

                    ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = absolute_x;
                    ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = y;

                }
            }

            if (create_actor_spell_effect(object, action_data, is_special,
                              (u16 *)((u8 *)owner + 0x98)) == 0) {
                return;
            }
            create_actor_linked_effect(object);
            ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B++;
            return;
        }

        ((R16_801725A4_S_801725A4_3 *)motion)->unk_14 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_10 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25));
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(object);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_6D--;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteAnimationTableView *)actor)->unk_14 |= 0x0800;
            return;
        }
        ((SpriteAnimationTableView *)actor)->unk_14 &= 0xF7FF;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B++;

    case 2:
        if (((SpriteAnimationTableView *)actor)->unk_04 != 4 || !(((SpriteAnimationTableView *)actor)->unk_14 & 0x1000)) {
            if ((((SpriteAnimationTableView *)actor)->unk_14 & 0xE000) == 0) {
                return;
            }
        }
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 |= 0x80;
        if ((((SpriteAnimationTableView *)actor)->unk_14 & 0xE000) == 0) {
            return;
        }

        ((R16_801725A4_S_801725A4_3 *)motion)->unk_14 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_10 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25));

        {
            u8 *direction_table = ((u8 *)D_8017420C);
            if (((SpriteAnimationTableView *)actor)->unk_2C != direction_table) {
                (*(u8 * *)((u8 *)actor + 0x2C)) = direction_table;
                func_80047784(
                    actor,(u8)(direction_table[((g_game_work.view.viewAngle + ((R16_801725A4_S_801725A4_1 *)object)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
        }

        {
            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
        }
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        advance_status_timers(object);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_6D--;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;
    default:
        return;
    }
}
