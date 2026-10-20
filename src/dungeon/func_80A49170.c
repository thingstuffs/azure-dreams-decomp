#include "modules/dungeon_resource06_slot0.h"

void start_selected_move_and_reset_action(void *action, EntityRec *position, void *sprite, EntityRec *actor)
{
    s32 phase;
    s16 is_special;
    s32 move_kind;
    u8 *move_data;
    void *target;
    s8 target_x;
    s8 target_y;
    u16 recovery_ticks;

    phase = ((R06_80172970_S_80172970_0 *)action)->unk_9B;
    is_special = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            move_kind = (actor->unk_46 & 0x3FFF) - 1;
            switch (move_kind) {
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                move_data = (u8 *)actor + 0xE;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                move_data = (u8 *)actor + 0xB;
                break;
            case 4:
                is_special = 1;
                /* fall through */
            case 0:
                move_data = (u8 *)actor + 8;
                break;
            default:
                move_data = 0;
                break;
            }
        } else {
            move_kind = actor->unk_46 & 0x3FFF;
            switch (move_kind) {
            case 3:
                move_data = (u8 *)actor + 0xE;
                break;
            case 2:
                move_data = (u8 *)actor + 0xB;
                break;
            case 1:
                move_data = (u8 *)actor + 8;
                break;
            default:
                move_data = 0;
                break;
            }
        }
        if (*move_data != 0) {
            ((R06_80172970_S_80172970_0 *)action)->unk_98 &= 0xFF7F;
            if (is_special != 0) {
                target = D_800814A8;
                actor->target = target;
                phase = ((R06_80172970_S_80172970_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((R06_80172970_S_80172970_3 *)phase)->unk_24;
                actor->unk_73 = ((R06_80172970_S_80172970_3 *)phase)->unk_25;
            } else if (D_8006DE24[*move_data].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    phase = ((R06_80172970_S_80172970_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((R06_80172970_S_80172970_3 *)phase)->unk_24;
                    actor->unk_73 = ((R06_80172970_S_80172970_3 *)phase)->unk_25;
                }
            } else {
                actor->target =
                    scan_monster_along_heading(actor,
                    ((R06_80172970_S_80172970_4 *)sprite)->unk_24,
                    ((R06_80172970_S_80172970_4 *)sprite)->unk_25,
                    actor->facing, 0x10);
                target_x = actor->unk_72;
                target_y = actor->unk_73;
                target_x = abs(target_x);
                target_y = abs(target_y);
                actor->unk_72 = target_x;
                actor->unk_73 = target_y;

            }

            ((R06_80172970_S_80172970_0 *)action)->unk_98 |= 0x1000;
            if (create_actor_spell_effect(actor, move_data,(s16)(is_special),
                (u16 *)((u8 *)action + 0x98)) == 0) {
                return;
            }
            ((R06_80172970_S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            ((R06_80172970_S_80172970_0 *)action)->unk_96 = 0xE;
            ((R06_80172970_S_80172970_0 *)action)->unk_9B++;
            return;
        }

        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, ((R06_80172970_S_80172970_4 *)sprite)->unk_24, ((R06_80172970_S_80172970_4 *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((R06_80172970_S_80172970_0 *)action)->unk_8C = ((u8 *)initialize_destination_state);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((R06_80172970_S_80172970_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((R06_80172970_S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
        ((R06_80172970_S_80172970_0 *)action)->unk_9B++;

    case 2:
        recovery_ticks = ((R06_80172970_S_80172970_0 *)action)->unk_96 - 1;
        ((R06_80172970_S_80172970_0 *)action)->unk_96 = recovery_ticks;
        if ((s32)(recovery_ticks << 16) > 0) {
            if (!(((R06_80172970_S_80172970_4 *)sprite)->unk_14 & 0xE000)) {
                return;
            }
        }
        ((R06_80172970_S_80172970_0 *)action)->unk_98 |= 0x80;
        if (!(((R06_80172970_S_80172970_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, ((R06_80172970_S_80172970_4 *)sprite)->unk_24, ((R06_80172970_S_80172970_4 *)sprite)->unk_25);
        if (((R06_80172970_S_80172970_4 *)sprite)->unk_2C != ((u8 *)D_8017586C)) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017586C);
            select_sprite_entry(
                sprite,
                ((u8 *)D_8017586C)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((R06_80172970_S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
        ((R06_80172970_S_80172970_0 *)action)->unk_8C = ((u8 *)initialize_destination_state);
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    default:
        return;
    }
}

/* MECHANISM: The 0x38 frame naturally holds args in s3/s4/s2/s1, with s5 state and s0 choice. Carrying
   the loaded object through the copy join removes a redundant lw+nop pair. A kept special-test copy
   restores move v0,s5; holding the copied record in v1 closes the final four register-field
   substitutions. */
