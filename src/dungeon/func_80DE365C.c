#include "modules/dungeon_ovl_e0365c.h"

void update_actor_behavior_facing_and_animation_2(void *actor_in, void *context_in, void *sprite_in, void *status_in)
{
    void *status;
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 initial_flags = g_dungeon_status.flags;

    status = status_in;

    if (initial_flags & 0x1000) {
        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xE;
        advance_actor_path_step(actor_in, context_in, sprite_in, status);
        return;
    }


    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_25 == 0) {
        advance_actor_pending_action(actor_in, context_in, sprite_in, status);
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174530;
        select_sprite_entry(sprite_in,
            D_80174530[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xD;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9B = 1;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_8C = 0;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_in, context_in, sprite_in, D_80174530)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_in, context_in, sprite_in, status);
            return;
        }

        {
            s32 next_state;
            s32 actor_state;

            actor_state = ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A;
            next_state = 0xE;

            if (actor_state != next_state) {
                anim_table = D_80174520;
                if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    select_sprite_entry(sprite_in,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_98 &= 0xFFF3;
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, context_in, sprite_in, D_80174548)) {
                return;
            }
        }

        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, context_in, sprite_in, status);
            update_actor_landing_and_trap(actor_in, context_in, sprite_in, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor_in, context_in, sprite_in, status);
        }
    }

    tile_record = find_active_rect_containing_point(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v);
    ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_26 = tile_record;

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x20) {
            update_actor_status_and_food(status);
            return;
        }
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
            return;
        }
        if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(status,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)select_actor_relation_state(actor_in, context_in, sprite_in, 0) == 0) {
                return;
            }
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
                return;
            }
        }

        switch (((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)begin_actor_directional_attack(actor_in, context_in, sprite_in, status) == 0) {
                begin_actor_attack_after_status_check(actor_in, context_in, sprite_in, status);
            }
            return;

        case 9:
            if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x400) {
                s32 movement_flags;

                movement_flags = ((E_80170E5C_S_80170E5C_1 *)status)->unk_14;

                if (!(movement_flags & 0x80000000)) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_14 = movement_flags | 0x80000000;
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            }
            if ((s16)check_actor_ahead_height(actor_in, context_in, sprite_in, status) != 0) {
                return;
            }
            start_actor_directional_animation(actor_in, context_in, sprite_in, status);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *active_actor;
            s32 direction;

            direction = get_rounded_facing_and_rounding_flag(
                ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                &direction_aux);
            active_actor = D_800814A8;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = direction;
            if (active_actor->unk_9A == 0x11) {
                begin_actor_spell_action(actor_in, context_in, sprite_in, D_80174560, update_actor_behavior_facing_and_animation_2);
                return;
            }
        }

        case 12:
            update_actor_status_and_food(status);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, context_in, sprite_in, D_80174560, update_actor_behavior_facing_and_animation_2);
            return;

        case 11:
        case 4:
        default:
            update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
            return;
        }
    } else if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v,
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v, D_80082E80.tile_position.parts.tile_x,
                        D_80082E80.tile_position.parts.tile_y) != 0) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174520;
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

update_table:
    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    select_sprite_entry(sprite_in,
        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
