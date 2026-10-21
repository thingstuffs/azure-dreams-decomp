/* Relinked copy of dungeon/func_80B43670 (func_80B43670.c); retail differs only at relocation sites. */
#include "modules/dungeon_resource12_slot0.h"

/* r121_nodonor relink of dungeon/func_80B43670: symbols this copy binds at other addresses. */
void func_8014D3E0(void *controller, void *context, void *entity, void *path_state);
extern u8 D_80150DB4[];
extern u8 D_80150DAC[];
extern u8 D_80150D4C[];
extern u8 D_80150D54[];
void func_8014FD94(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object);
void func_8015052C(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
s32 func_8014E0C0(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
s32 func_8014DDE4(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_8014DFA8(void *action_state, void *action_context, void *sprite, EntityRec *actor);
void func_8014DFA8(void *action_state, void *action_context, void *sprite, EntityRec *actor);
extern u8 D_80150D94[];
void func_8014D638(void *move_data, void *context, void *position_data, void *actor_data);

void choose_unicorn_action_slot_a(void *entity, void *context, void *sprite, void *actor)
{
    u8 *effect_table;
    s32 next_state;
    s16 path_distance;
    s16 target_angle;
    s32 actor_flags;
    s32 action_index;
    s8 tile_id;
    s32 current_state;
    u16 action_flags;
    EntityRec *owner;

    if (g_dungeon_status.flags & 0x1000) {
        ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 14;
        func_8014D3E0(entity, context, sprite, actor);
        return;
    }


    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_25 == 0) {
        advance_actor_pending_action(entity, context, sprite, actor);
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80150DB4)) {
            return;
        }
        {
            u8 *effects = ((u8 *)D_80150DAC);
            (*(void * *)((u8 *)sprite + (0x2C))) = effects;
            select_sprite_entry(
                sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                0);
        }
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80150DB4)) {
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 13;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9B = 1;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_8C = 0;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, ((u8 *)D_80150DAC)) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x100) {
            begin_pushed_actor_move(entity, context, sprite, actor);
            return;
        }

        current_state = ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = ((u8 *)D_80150D4C);

            if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C != effect) {
                (*(void * *)((u8 *)sprite + (0x2C))) = effect;
                select_sprite_entry(
                    sprite,(u8)(effect[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((R12_80170E70_S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, ((u8 *)D_80150D54)) != 0) {
                return;
            }
        }

        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            func_8014FD94(entity, context, sprite, actor);
            return;
        }

        if ((s16)can_entity_gain_level(actor) != 0) {
            if ((s16)process_selected_actor_record(entity, context, sprite, actor) != 0) {
                func_8015052C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = ((s8)find_active_rect_containing_point((u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v),(u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v)));
    ((R12_80170E70_S_80170E70_2 *)sprite)->unk_26 = tile_id;

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x20) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8014D638(entity, context, sprite, actor);
            return;
        }

        action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        actor, (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8014E0C0(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8014D638(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((R12_80170E70_S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_8014DDE4(entity, context, sprite, actor) != 0) {
                return;
            }
            func_8014DFA8(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = ((s16)get_rounded_facing_and_rounding_flag(
                ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v, ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_distance));
            owner = primary_actor_record;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80150D94), ((u8 *)choose_unicorn_action_slot_a));
                return;
            }

        case 11:
            update_actor_status_and_mp(actor);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80150D94), ((u8 *)choose_unicorn_action_slot_a));
            return;

        default:
            func_8014D638(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((dungeon_rooms[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)test_neighbor_position_relation((u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v),(u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v),(u8)(reference_tile_object.tile_position.parts.tile_x),(u8)(reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
                        ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v, ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_distance));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    effect_table = ((u8 *)D_80150D4C);
    if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == effect_table) {
        return;
    }
    {
        u8 *effects = effect_table;
        (*(void * *)((u8 *)sprite + (0x2C))) = effects;
        select_sprite_entry(
            sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
            0);
    }
}
