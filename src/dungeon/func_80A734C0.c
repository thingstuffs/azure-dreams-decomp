#include "modules/dungeon_resource07_slot0.h"

void advance_actor_stored_path_2(void *action, EntityRec *motion, void *sprite, void *actor) {
    u16 pos[3];
    s16 is_special;
    u8 *item;
    void *node;
    u8 *state;

    is_special = 0;
    state = (u8 *)(((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8);
    switch ((u8)state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            u32 kind = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (kind) {
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                item = (u8 *)actor + 0xE;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                item = (u8 *)actor + 0xB;
                break;
            case 4:
                is_special = 1;
                /* fall through */
            case 0:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        } else {
            s32 kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (kind) {
            case 3:
                item = (u8 *)actor + 0xE;
                break;
            case 2:
                item = (u8 *)actor + 0xB;
                break;
            case 1:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        }
        if (*item != 0) {

            ((Rec_func_80172CC0_arg0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_existing;

                use_existing = is_special;
                if (use_existing) {
                    node = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = node;
                    goto copy_existing;
                }
            }

            {
                u8 *item_table = D_8006DE24;
                u8 item_id = *item;
                u8 *item_entry = item_table + item_id * 20;
                if (item_entry[0x12] == 2) {
                    node = (*(void * *)((u8 *)actor + 0x60));
                    if (node != 0) {
copy_existing:
                        {

                            state = ((R07_80172CC0_S_80172CC0_1_pre *)node)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((R07_80172CC0_S_80172CC0_2 *)state)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((R07_80172CC0_S_80172CC0_2 *)state)->unk_25;
                        }

                    }
                } else {
                    s8 x;
                    s8 y;

                    ((EntityRec *)actor)->target = (void *)scan_monster_along_heading(
                        actor,
                        ((Rec_D_80082E80 *)sprite)->unk_24,
                        ((Rec_D_80082E80 *)sprite)->unk_25,
                        ((EntityRec *)actor)->facing,
                        0x10);
                    x = ((EntityRec *)actor)->unk_72;
                    y = ((EntityRec *)actor)->unk_73;
                    x = abs(x);
                    y = abs(y);
                    ((EntityRec *)actor)->unk_72 = x;
                    ((EntityRec *)actor)->unk_73 = y;
                }
            }

            pos[0] = ((u16)motion->x.w.i);
            pos[1] = ((u16)motion->y.w.i);
            pos[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, item, is_special, (u8 *)action + 0x98)) {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(pos, (s16)((*item - 1) % 3));
                ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
                return;
            }
            return;

        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        g_dungeon_status.unk_0C = 0;
        {
            u8 *active_entity = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_entity + 0xA6))--;
        }
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = ((void *)func_80170E54);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;
    case 1:
        item = (u8 *)(s32)get_cd_command_queue_depth();
        if (item) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
                        /* fall through */

    case 2:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174180);
        func_80047784(
            sprite,
            ((u8 *)D_80174180)[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
            0);
        ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = 0x10;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
        return;

    case 3:
        {
            s16 sound_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_A8 - 1;
            ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = sound_timer;
            if (sound_timer == 0) {
                play_sound_if_enabled(0x610);
            }
        }

        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 12 &&
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0x10;
            ((Rec_func_80172CC0_arg0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 anim_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 - 1;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = anim_timer;
            if ((s16)anim_timer <= 0) {
                ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }

        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pv != ((u8 *)D_80174148)) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174148);
            func_80047784(
                sprite,
                ((u8 *)D_80174148)[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = ((void *)func_80170E54);
        advance_status_timers(actor);
        if ((*(s8 *)((u8 *)actor + 0x6D)) > 0) {
            (*(u8 *)((u8 *)actor + 0x6D))--;
        }
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;

    default:
        break;
    }

    return;
}
