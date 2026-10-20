#include "modules/dungeon_resource03_slot0.h"

void finish_timed_actor_movement(void *action_state, void *transform, void *sprite, EntityRec *actor)
{
    u16 position[4];
    u8 *motion;
    s16 use_player_target;
    SpriteLinkPrefixView *target;
    s32 delay;
    MovingTile *action_status;

    use_player_target = 0;
    switch (((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player_target = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player_target = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 player_target = use_player_target;
                if (player_target != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    action_status = (u8 *)target[-1].unk_00;
                    actor->unk_72 = action_status->unk_24;
                    actor->unk_73 = action_status->unk_25;
                } else if (D_8006DE24[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_status = (u8 *)target[-1].unk_00;
                        actor->unk_72 = action_status->unk_24;
                        actor->unk_73 = action_status->unk_25;
                    }
                } else {
                    actor->target =
                        scan_monster_along_heading(actor,(u8)(((Rec_D_80082E80 *)sprite)->unk_24),(u8)(((Rec_D_80082E80 *)sprite)->unk_25),(s16)(actor->facing), 0x10);
                    actor->unk_72 = abs(actor->unk_72);
                    actor->unk_73 = abs(actor->unk_73);
                }
            }
            position[0] = ((u16)((EntityRec *)transform)->x.w.i);
            position[1] = ((u16)((EntityRec *)transform)->y.w.i);
            position[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)create_actor_spell_effect(actor, motion,(s16)(use_player_target), (u8 *)action_state + 0x98);
            if (transform == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(position,(s16)((*motion - 1) % 3));
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)(((Rec_D_80082E80 *)sprite)->unk_24),(u8)(((Rec_D_80082E80 *)sprite)->unk_25));
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_8C = ((u8 *)func_80170E54);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000))
            ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = 0x3;
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_98 |= 0x80;
        }
        delay = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 - 1;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = delay;
        if ((s16)delay <= 0) {
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)(((Rec_D_80082E80 *)sprite)->unk_24),(u8)(((Rec_D_80082E80 *)sprite)->unk_25));
        {
            u8 *direction_table = ((u8 *)D_80173C7C);

            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_status = (u8 *)&g_dungeon_status.unk_00;
        if (((R03_80172A24_S_80172A24_7 *)action_status)->unk_0C != 0) {
            return;
        }
        ((R03_80172A24_S_80172A24_7 *)action_status)->unk_0A = ((R03_80172A24_S_80172A24_7 *)action_status)->unk_0A - 1;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_8C = ((u8 *)func_80170E54);
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}
