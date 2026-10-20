#include "modules/dungeon_resource08_slot0.h"

void advance_effect_and_child_animation(void *effect_state, EntityRec *position, Rec_D_80082E80 *entity, void *actor)
{
    u8 state;
    s32 effect_id;
    s32 direction;
    u8 mode;
    u16 angle;
    u16 saved_angle;
    R08_80174648_S_80174648_2 *effect_work = ((u8 *)(&g_game_work));
    state = ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B;
    if (state >= 9) {
        return;
    }
    switch (state) {
    case 0:
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
        return;

    case 1:
        run_cd_image_commands(((u8 *)D_80174CF4), ((u8 *)D_80174D18), 0);
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_B0 = 0;
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
        saved_angle = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
        ((R08_80174648_S_80174648_1 *)actor)->unk_8A = saved_angle;
        /* fallthrough */

    case 2:
        direction = ((g_game_work.view.viewAngle + ((R08_80174648_S_80174648_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        mode = ((u8 *)((void * *)D_80174D1C))[-4];
        angle = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
        if ((mode == 0) || (direction != 2)) {
            if (direction == 2) {
                return;
            }
            ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        run_cd_image_commands((u8 *)((void * *)D_80174CFC) - 8, (u8 *)((void * *)D_80174D1C) - 4, 1);
        sound_set_cd_cue_parameters(0, ((s32 *)D_8006CD58)[0], 0x04000AD4, 0x05000CC4);
        effect_id = func_800445E0();
        Control_CD(0x15, effect_id, 0);
        ((u8 *)D_80174D19)[0] = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_80174D19));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;

    case 3:
        {
            s32 frames_left;
            u8 effect_ready;
            u8 *target_color;

            frames_left = ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u = frames_left - 1;
            if ((s16)(frames_left - 1) <= 0) {
                effect_ready = ((u8 *)D_80174D19)[0];
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u = frames_left;
                if (effect_ready != 0) {
                    ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
                    play_sound_if_enabled(0x300);
                    return;
                }
                return;
            }
            target_color = ((void * *)D_800DCEEC)[lookup_masked_byte_table(actor)];
            effect_work->unk_A8 += (((R08_80174648_S_80174648_3 *)target_color)->unk_00
                - effect_work->unk_A8) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            effect_work->unk_A9 += (((R08_80174648_S_80174648_3 *)target_color)->unk_01
                - effect_work->unk_A9) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            effect_work->unk_AA += (((R08_80174648_S_80174648_3 *)target_color)->unk_02
                - effect_work->unk_AA) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            return;
        }

    case 4:
        {
            s16 variant;
            s32 color;
            s32 pos_z;

            effect_work = func_8003FC64(0x12);
            if (effect_work == 0) {
                return;
            }
            effect_work->unk_10.p = ((u8 *)func_8017451C);
            register_node(effect_work, ((u8 *)start_bank_actor_hit_reaction));
            color = 0x00808080;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_AC = effect_work;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_00 = position->x.v;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_04 = position->y.v;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_08 =
                (pos_z = position->z.v, ((s16 *)D_80174D14)[0] = 5, pos_z);
            effect_work = effect_work->unk_0C.p;
            effect_work->unk_1E = 0x1000;
            effect_work->unk_1C = 0x1000;
            effect_work->unk_0C.i = color;
            variant = lookup_masked_byte_table(actor) - 1;
            if (variant < 0) {
                variant = func_80069EF8() % 3;
            }
            func_8003DB94(effect_work, ((u8 *)D_8014A000) + (s32)((void * *)D_80174CFC)[variant], 0);
            entity->unk_14.at00_u16.v |= 0x80;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            create_positioned_sprite_effect(effect_state, position, entity);
            return;
        }

    case 5:
        {
            effect_work = ((R08_80174648_S_80174648_0 *)effect_state)->unk_AC;
            effect_work = effect_work->unk_0C.p;
            if (effect_work->unk_14 & 0xE000) {
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
                decrement_monster_entry_count(((R08_80174648_S_80174648_1 *)actor)->unk_13, 3);
                update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
                unlink_entity_node(actor);
                effect_work = (u8 *)actor - 0x20;
                effect_work->unk_10.i |= 0x80000000;
            }
    case 6:
            if (((R08_80174648_S_80174648_0 *)effect_state)->unk_9B != 6) {
                return;
            }
        }

        {
            if (create_status_linked_render_effect(position, ((void * *)D_80174D1C)[0], ((s16 *)D_80174D14)[0], ((s32 *)D_800DCF5C)) == 0) {
                return;
            }
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            decrement_monster_entry_count(((R08_80174648_S_80174648_1 *)actor)->unk_13, 3);
            update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
            unlink_entity_node(actor);
            effect_work = (u8 *)actor - 0x20;
            effect_work->unk_10.i |= 0x80000000;
            return;
        }

    case 7:
        {
            s32 child_or_angle;
            R08_80174648_S_80174648_7 *child_sprite;
            s32 direction;

            if ((((R08_80174648_S_80174648_1 *)actor)->unk_60.p = advance_staged_entity_load(entity, actor)) == 0) {
                return;
            }
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            ((R08_80174648_S_80174648_10 *)(((R08_80174648_S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
            child_or_angle = ((R08_80174648_S_80174648_1 *)actor)->unk_60.i;
            child_sprite = ((R08_80174648_S_80174648_6_pre *)((void *)child_or_angle))[-1].unk_00;
            child_or_angle = ((R08_80174648_S_80174648_6 *)((void *)child_or_angle))->unk_2A;
            direction = (g_game_work.view.viewAngle + child_or_angle + 0x100) >> 9;
            direction &= 7;
            select_indirect_table_entry(child_sprite, ((R08_80174648_S_80174648_11 *)(child_sprite->unk_2C + direction))->unk_00,
                child_sprite->unk_04);
            child_sprite->unk_14 &= 0xFFFE;
        }

    case 8:
        {

            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u--;
            if (((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s > 0) {
                return;
            }
            ((R08_80174648_S_80174648_10 *)(((R08_80174648_S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((R08_80174648_S_80174648_1 *)actor)->unk_8A;
            ((R08_80174648_S_80174648_0_pre *)effect_state)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            g_dungeon_status.unk_0A--;
            ((R08_80174648_S_80174648_1 *)actor)->unk_6D = 0;
        }
        }
}
