#include "modules/dungeon_resource12_slot0.h"
#include "shared/sprite_frame_state.h"

void advance_action_and_spawn_effect(void *action, void *motion, void *entity, void *actor) {
    s16 effect_offset[3];
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 state;
    s32 timer;
    u8 next_state;
    s32 shifted_timer;
    void *action_actor;
    void *effect;
    u8 *effect_data;

    state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.s;
    dir_offset = (((R12_80172654_S_80172654_1 *)actor)->unk_2A.s >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + dir_offset);
    dir_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + dir_offset);
    timer = ((R12_80172654_S_80172654_0 *)action)->unk_96.s - 1;
    ((R12_80172654_S_80172654_0 *)action)->unk_96.s = timer;

    switch (state) {
    case 0:
        action_actor = actor;
        if (((SpriteFrameState *)entity)->flags & 0x8000) {
            ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = 0xFF;
            ((SpriteFrameState *)entity)->flags |= 0x6000;
            resolve_attack_damage_and_effects(action_actor, entity,(s16)(((R12_80172654_S_80172654_3 *)action_actor)->unk_2A),(s16)(1));
            return;
        }
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C = (-dir_x) << 17;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 = (-dir_y) << 17;
        ((R12_80172654_S_80172654_4 *)motion)->unk_14 = 0;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A4C)[((g_game_work.view.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        timer = 8;
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = timer;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 1:
        shifted_timer = timer << 16;
        if (shifted_timer > 0)
            return;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 = 0;
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C = 0;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A8C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A8C)[((g_game_work.view.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 2:
        if (((((SpriteFrameState *)entity)->unk_04 == 4) &&
             (((SpriteFrameState *)entity)->flags & 0x1000)) ||
            (((SpriteFrameState *)entity)->flags & 0x8000)) {
            ((SpriteFrameState *)entity)->flags |= 0x800;
            ((R12_80172654_S_80172654_0 *)action)->unk_96.s = 0x10;
            if (resolve_record_orientation_or_fallback(*(s32 *)&((SpriteFrameState *)entity)->source, entity, effect_offset,(s16)(0)) == 0) {
                effect_offset[2] = 0;
                effect_offset[1] = 0;
                effect_offset[0] = 0;
            }
            effect = allocate_list_node(0x12, ((u8 *)(&D_80083498)));
            if (effect != NULL) {
                register_node(effect, ((u8 *)build_linked_curved_wireframe_grid));
                ((R12_80172654_S_80172654_5 *)effect)->unk_10 = ((u8 *)dim_effect_after_delay);
                ((R12_80172654_S_80172654_5 *)effect)->unk_20 = ((R12_80172654_S_80172654_4 *)motion)->unk_00.at02.v + effect_offset[0];
                effect_data = (u8 *)effect + 0x20;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_02 = ((R12_80172654_S_80172654_4 *)motion)->unk_04.at02.v + effect_offset[1];
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_04 = ((R12_80172654_S_80172654_4 *)motion)->unk_0A + effect_offset[2];
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_08 = 0xC0C0C0;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_0E = 8;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_12 =
                    sample_terrain_surface_height(((((SpriteFrameState *)entity)->unk_24 + dir_x) << 6) & 0xFFC0,
                                  ((((SpriteFrameState *)entity)->unk_25 + dir_y) << 6) & 0xFFC0,(s16)((s16)(((R12_80172654_S_80172654_4 *)motion)->unk_0A - 0x80))) -
                    ((R12_80172654_S_80172654_4 *)motion)->unk_0A;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_10 = ((R12_80172654_S_80172654_1 *)actor)->unk_2A.s;
            }
            next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
            next_state += 1;
            ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
            return;
        }
        return;
    case 3:
        if ((s16)timer == 0xA) {
            resolve_attack_damage_and_effects(actor, entity,(s16)(((R12_80172654_S_80172654_1 *)actor)->unk_2A.u),(s16)(1));
            play_sound_if_enabled(0x813);
        }
        if (((R12_80172654_S_80172654_0 *)action)->unk_96.u > 0)
            return;
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = 8;
        ((SpriteFrameState *)entity)->flags &= 0xF7FF;
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 4:
        if ((timer << 16) > 0)
            return;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A4C)[((g_game_work.view.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = state;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = 0xFF;
        return;
    case 0xFF:
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C =
            (s32)((((((SpriteFrameState *)entity)->unk_24 << 6) + 0x20) << 16) -
                  ((R12_80172654_S_80172654_4 *)motion)->unk_00.at00.v) >> 1;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 =
            (s32)((((((SpriteFrameState *)entity)->unk_25 << 6) + 0x20) << 16) -
                  ((R12_80172654_S_80172654_4 *)motion)->unk_04.at00.v) >> 1;
        if ((((SpriteFrameState *)entity)->flags & 0xE000) ||
            (((R12_80172654_S_80172654_0 *)action)->unk_96.u <= 0)) {
            ((R12_80172654_S_80172654_4 *)motion)->unk_14 = 0;
            ((R12_80172654_S_80172654_4 *)motion)->unk_10 = 0;
            ((R12_80172654_S_80172654_4 *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion,(u8)((SpriteFrameState *)entity)->unk_24,(u8)((SpriteFrameState *)entity)->unk_25);
            reduce_actor_food_meter(actor, 0x100);
            ((R12_80172654_S_80172654_0 *)action)->unk_8C = ((void *)update_actor_state_and_select_target);
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            if (((R12_80172654_S_80172654_1 *)actor)->unk_6D == 0) {
                ((R12_80172654_S_80172654_1 *)actor)->unk_46 &= 0x7FFF;
                return;
            }
            (*(void * *)D_800E3DE8) = (u8 *)actor - 0x20;
        }
        return;
    default:
        return;
    }
}
