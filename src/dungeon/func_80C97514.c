#include "modules/dungeon_ovl_cb3000.h"

void func_80174D14(void *state, EntityRec *position, Rec_D_80082E80 *entity, void *actor) {
    s16 direction;
    u16 fade_ticks;
    u16 finish_ticks;
    u16 previous_ticks;
    u8 status;
    u8 next_state;
    CB_80174D14_S_80C97514_4 *effect_data;
    GameWork *scene_color = &g_game_work;
    CB_80174D14_S_80C97514_7 *render_obj;
    CB_80174D14_S_80C97514_5 *effect;
    void *new_model;
    void *model;

    status = ((CB_80174D14_S_80C97514_0 *)state)->unk_9B;
    switch (status) {
    case 0:
        next_state = ((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = next_state;
        return;
    case 1:
        func_80041588(&D_8017530C, &D_801753A8, 0);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_A4 = 0;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
        ((Rec_D_80082E80 *)actor)->unk_8A = (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
    case 2:
        direction = ((s32) (g_game_work.view.viewAngle + (s16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)&D_801753A8) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x200);
            return;
        }

        func_80041588(&D_8017530C, &D_801753A8, 1);
        sound_set_cd_cue_parameters(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), NULL);
        (*(s8 *)&D_801753A9) = 0;
        Control_CD(0xFF, &D_8003E140, &D_801753A9);
        select_nearby_target_and_initialize_slot(actor - 0x20, position, 8, 0x300);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
        create_radial_effect_bands(state, position, entity);
    case 3:
        previous_ticks = ((CB_80174D14_S_80C97514_0 *)state)->unk_96;
        fade_ticks = previous_ticks - 1;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            status = ((CB_80174D14_S_80C97514_2 *)(&D_801753A9))->unk_00;
            ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = previous_ticks;
            if (status == 0) {
                return;
            }
            ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
            play_sound_if_enabled(0x300);
            return;
        }
        effect_data = ((void **)&D_800DCEEC)[lookup_masked_byte_table(actor)];
        scene_color->view.unk_090 = (u8) (scene_color->view.unk_090 + ((s32) (effect_data->unk_00
            - scene_color->view.unk_090) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->unk_96));
        scene_color->view.unk_091 = (u8) (scene_color->view.unk_091 + ((s32) (effect_data->unk_01
            - scene_color->view.unk_091) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->unk_96));
        scene_color->view.unk_092 = (u8) (scene_color->view.unk_092 + ((s32) (effect_data->unk_02
            - scene_color->view.unk_092) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->unk_96));
        return;
    case 4:
    {
        s32 effect_type;
        s16 effect_index;

        effect = func_8003FC64(0x12);
        if (effect == NULL) {
            return;
        }
        effect->unk_10 = func_80174BE8;
        func_8004491C(effect, func_80045340);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_AC = effect;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_00 = (s32) position->x.v;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_04 = (s32) position->y.v;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_08 = (s32) position->z.v;
        render_obj = effect->unk_0C;
        render_obj->unk_1E = 0x1000;
        render_obj->unk_1C = 0x1000;
        render_obj->unk_0C.s = 0x808080;
        effect_type = lookup_masked_byte_table(actor) - 1;
        effect_index = effect_type;
        if ((effect_type << 0x10) < 0) {
            effect_index = func_80069EF8() % 3;
        }
        effect_data = (void *)(*((s32 *)&D_80175318 + (s16) effect_index) + (s32)&D_8014A000);
        func_8003DB94(render_obj, effect_data, 0);
        entity->unk_14.at00_u16.v = (u16) (entity->unk_14.at00_u16.v | 0x80);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = 0U;
        next_state = ((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = next_state;
        return;
    }
    case 5:
        render_obj = ((CB_80174D14_S_80C97514_0 *)state)->unk_AC;
        render_obj = render_obj->unk_0C.u;
        if (render_obj->unk_14 & 0xE000) {
            ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
        }
    case 6:
        if (((CB_80174D14_S_80C97514_0 *)state)->unk_9B != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, D_801753AC, D_80175314, &D_800DCF5C) == 0) {
            return;
        }
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
        unlink_entity_node(actor);
        render_obj = actor - 0x20;
        render_obj->unk_10 = (s32) (render_obj->unk_10 | 0x80000000);
        return;
    case 7:
        new_model = advance_staged_entity_load(entity, actor);
        ((Rec_D_80082E80 *)actor)->unk_60.as_pv = new_model;
        if (new_model == NULL) {
            return;
        }
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_9B = (u8) (((CB_80174D14_S_80C97514_0 *)state)->unk_9B + 1);
        ((CB_80174D14_S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A =
            (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
        model = ((Rec_D_80082E80 *)actor)->unk_60.as_pv;
        render_obj = ((CB_80174D14_S_80C97514_9_pre *)model)[-1].unk_00;
        select_indirect_table_entry(render_obj, render_obj->unk_2C[((s32) (g_game_work.view.viewAngle
            + (s16) ((CB_80174D14_S_80C97514_9 *)model)->unk_2A + 0x100) >> 9) & 7], render_obj->unk_04);
        render_obj->unk_14 = (u16) (render_obj->unk_14 & 0xFFFE);
    case 8:
        finish_ticks = ((CB_80174D14_S_80C97514_0 *)state)->unk_96 - 1;
        ((CB_80174D14_S_80C97514_0 *)state)->unk_96 = finish_ticks;
        if ((finish_ticks << 0x10) > 0) {
            return;
        }
        ((CB_80174D14_S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)actor)->unk_8A;
        ((CB_80174D14_S_80C97514_0_pre *)state)[-1].unk_00 = (u16) (((CB_80174D14_S_80C97514_0_pre *)state)[-1].unk_00 | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        ((Rec_D_80082E80 *)actor)->unk_6D = 0;
        return;
    }
}
