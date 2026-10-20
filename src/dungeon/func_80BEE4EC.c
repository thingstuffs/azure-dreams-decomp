#include "modules/dungeon_resource16_slot0.h"
#include "shared/sprite_frame_state.h"

void advance_actor_effect_sequence(Rec_func_801732A4_arg0 *state, EntityRec *position, Rec_D_80082E80 *actor, void *model) {
    s16 next_spawn;
    s16 next_trail;
    s16 spawn_count;
    s16 trail_count;
    s32 direction;
    s32 color;
    s32 variant_index;
    s16 effect_value;
    s32 effect_value_2;
    u16 fade_left;
    u16 elapsed;
    u16 fade_timer;
    s32 event_done;
    u8 phase;
    void *effect_model;
    R16_80173CEC_S_80173CEC_4 *target_color;
    R16_80173CEC_S_80173CEC_8 *effect_position;
    R16_80173CEC_S_80173CEC_9 *effect_sprite;
    GameWork *scene_color;
    R16_80173CEC_S_80173CEC_5 *effect;

    scene_color = &g_game_work;
    phase = state->unk_9B;
    switch (phase) {
    case 0:
        state->unk_9B = (u8) (state->unk_9B + 1);
        return;
    case 1:
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)D_801742E4), 0);
        state->unk_A6 = 0;
        state->unk_9B = (u8) (state->unk_9B + 1);
        ((Rec_D_80082E80 *)model)->unk_8A = (u16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v;
        ((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v =
            (s32) (((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v & 0xFFFBFFFF);
    case 2:
        direction = ((s32) (g_game_work.view.viewAngle + (s16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)((s32 *)D_801742E4)) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x200);
            return;
        }
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)D_801742E4), 1);
        sound_set_cd_cue_parameters(0, (*(s32 *)D_8006CD58), 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), NULL);
        (*(s8 *)((s32 *)D_801742E5)) = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((s32 *)D_801742E5));
        select_nearby_target_and_initialize_slot(model - 0x20, position, 8, 0x300);
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 3:
        fade_timer = state->unk_96;
        fade_left = fade_timer - 1;
        state->unk_96 = fade_left;
        if ((fade_left << 0x10) <= 0) {
            event_done = ((R16_80173CEC_S_80173CEC_2 *)(((s32 *)D_801742E5)))->unk_00;
            state->unk_96 = fade_timer;
            if (event_done == 0) {
                return;
            }
            state->unk_9B = (u8) (state->unk_9B + 1);
            play_sound_if_enabled(0x300);
            return;
        }
        target_color = (*(void **)((u8 *)(((s32 *)D_800DCEEC)) + lookup_masked_byte_table(model) * 4));
        scene_color->view.unk_090 = (u8) (scene_color->view.unk_090 + ((s32) (target_color->unk_00
            - scene_color->view.unk_090) / (s16) state->unk_96));
        scene_color->view.unk_091 = (u8) (scene_color->view.unk_091 + ((s32) (target_color->unk_01
            - scene_color->view.unk_091) / (s16) state->unk_96));
        scene_color->view.unk_092 = (u8) (scene_color->view.unk_092 + ((s32) (target_color->unk_02
            - scene_color->view.unk_092) / (s16) state->unk_96));
        return;
    case 4:
        effect = func_8003FC64(0x12);
        if (effect == NULL) {
            return;
        }
        effect->unk_10 = ((void *)fade_entity_colors_to_neutral);
        register_node(effect, ((void *)func_801736AC));
        color = 0x808080;
        state->unk_AC = effect;
        effect_model = model;
        ((R16_80173CEC_S_80173CEC_12 *)(((R16_80173CEC_S_80173CEC_11 *)effect)->unk_08))->unk_00 = (s32) position->x.v;
        ((R16_80173CEC_S_80173CEC_12 *)(((R16_80173CEC_S_80173CEC_11 *)effect)->unk_08))->unk_04 = (s32) position->y.v;
        effect_position = effect->unk_08;
        effect_value_2 = position->z.v;
        (*(s16 *)D_801742E0) = -8;
        effect_position->unk_08 = effect_value_2;
        effect_sprite = effect->unk_0C;
        effect_sprite->unk_1E = 0x1000;
        effect_sprite->unk_1C = 0x1000;
        effect_sprite->unk_0C.s = color;
        variant_index = lookup_masked_byte_table(effect_model) - 1;
        effect_value = variant_index;
        if ((variant_index << 0x10) < 0) {
            effect_value = func_80069EF8() % 3;
        }
        func_8003DB94(effect_sprite, ((s32 *)D_801742D4)[(s16) effect_value] + (s8 *) ((s32 *)D_8014A000), 0);
        ((SpriteFrameState *)actor)->flags = (u16) (((SpriteFrameState *)actor)->flags | 0x80);
        spawn_count = 0;
        state->unk_96 = 0U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        do {
            create_angled_source_effect(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
            next_spawn = spawn_count + 1;
            spawn_count = next_spawn;
            if (next_spawn >= 8) {
                return;
            }
        } while (1);
    case 5:
        elapsed = state->unk_96;
        state->unk_96 = (u16) (elapsed + 1);
        if ((s16) elapsed < 0x1E) {
            trail_count = 0;
            do {
                create_angled_source_effect(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
                next_trail = trail_count + 1;
                trail_count = next_trail;
            } while (next_trail < 8);
        }
        effect_sprite = state->unk_AC;
        effect_sprite = effect_sprite->unk_0C.u;
        if (effect_sprite->unk_14 & 0xE000) {
            state->unk_9B = (u8) (state->unk_9B + 1);
        }
    case 6:
        if (state->unk_9B != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, (*(s32 *)D_801742E8), (*(s16 *)D_801742E0), ((s32 *)D_800DCF5C)) == 0) {
            return;
        }
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)model)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25, 0x300);
        unlink_entity_node(model);
        effect_sprite = model - 0x20;
        effect_sprite->unk_10 = (s32) (effect_sprite->unk_10 | 0x80000000);
        return;
    case 7:
        ((Rec_D_80082E80 *)model)->unk_60.as_s32 = advance_staged_entity_load(actor, model);
        return;
    }
}
