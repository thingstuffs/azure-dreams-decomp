#include "modules/dungeon_resource12_slot0.h"
#include "shared/sprite_frame_state.h"

void update_actor_state_and_select_target(void *entity, void *context, void *sprite, void *actor)
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
        advance_actor_path_script_step(entity, context, sprite, actor);
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_25 == 0) {
        advance_actor_pending_action(entity, context, sprite, actor);
        if (((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_80175A9C)) {
            return;
        }
        {
            u8 *effects = ((u8 *)D_80175A94);
            ((SpriteFrameState *)sprite)->frameTable = effects;
            select_sprite_entry(
                sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                0);
        }
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_80175A9C)) {
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 13;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9B = 1;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_8C = 0;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, ((u8 *)D_80175A94)) != 0) {
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
            u8 *effect = ((u8 *)D_80175A54);

            if (((SpriteFrameState *)sprite)->frameTable != effect) {
                ((SpriteFrameState *)sprite)->frameTable = effect;
                select_sprite_entry(
                    sprite,(u8)(effect[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((R12_80170E70_S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, ((u8 *)D_80175A5C)) != 0) {
                return;
            }
        }

        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            func_80173D64(entity, context, sprite, actor);
            return;
        }

        if ((s16)can_entity_gain_level(actor) != 0) {
            if ((s16)process_selected_actor_record(entity, context, sprite, actor) != 0) {
                func_8017526C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = ((s8)find_active_rect_containing_point((u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25));
    ((SpriteFrameState *)sprite)->unk_26 = tile_id;

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x20) {
            update_actor_status_and_food(actor);
            return;
        }
        if (*(u16 *)&((SpriteFrameState *)sprite)->unk_24 == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_8017162C(entity, context, sprite, actor);
            return;
        }

        action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        actor, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8017162C(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((R12_80170E70_S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_80171DD8(entity, context, sprite, actor) != 0) {
                return;
            }
            select_and_start_target_action(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = ((s16)get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &path_distance));
            owner = D_800814A8;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)update_actor_state_and_select_target));
                return;
            }

        case 11:
            update_actor_status_and_food(actor);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)update_actor_state_and_select_target));
            return;

        default:
            func_8017162C(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((D_800E2970[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)compare_monster_neighbor_values((u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25,(u8)(D_80082E80.tile_position.parts.tile_x),(u8)(D_80082E80.tile_position.parts.tile_y)) != 0) {
                    ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
                        ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &path_distance));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((SpriteFrameState *)sprite)->flags & 0x40) {
        return;
    }
    effect_table = ((u8 *)D_80175A54);
    if (((SpriteFrameState *)sprite)->frameTable == effect_table) {
        return;
    }
    {
        u8 *effects = effect_table;
        ((SpriteFrameState *)sprite)->frameTable = effects;
        select_sprite_entry(
            sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
            0);
    }
}
