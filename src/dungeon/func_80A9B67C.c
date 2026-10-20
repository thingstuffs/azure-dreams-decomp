#include "modules/dungeon_resource08_slot0.h"

void update_actor_behavior_and_effect(void *actor, EntityRec *position, SpriteFrameState *object, EntityRec *actor_data)
{
    s32 distance;
    s16 effect_offset[3];
    s8 room_id;
    u16 action_state;
    u8 *anim_table;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_801715B4(actor, position, object, actor_data);
        return;
    }

    if (actor_data->tileY == 0) {
        advance_actor_pending_action(actor, position, object, actor_data);
        if (object->frameTable == ((u8 *)D_80174C8C)) {
            return;
        }
        object->frameTable = ((u8 *)D_80174C84);
        select_sprite_entry(object,
            ((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)actor_data->flags1C) & 0x200) {
        if (object->frameTable == ((u8 *)D_80174C8C)) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            actor_data->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, position, object, ((u8 *)D_80174C84)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor_data->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, position, object, actor_data);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
            u32 idle_state;

            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = ((u8 *)D_80174C3C);
                if (object->frameTable != anim_table) {
                    object->frameTable = anim_table;
                    select_sprite_entry(object,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (actor_data->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, position, object, ((u8 *)D_80174C44)) != 0) {
                return;
            }
        }

        if (((u32)actor_data->flags1C) & 0x80000) {

            begin_actor_move_to_target_facing(actor, position, object, actor_data);
            func_80173F20(actor, position, object, actor_data);
            object->frameTable = ((u8 *)D_80174C34);
            select_sprite_entry(object,
                ((u8 *)D_80174C34)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
                0);
            return;
        }

        if ((can_entity_gain_level(actor_data) << 16) != 0) {
            if ((process_selected_actor_record(actor, position, object, actor_data) << 16) != 0) {
                func_80174470(actor, position, object, actor_data);
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(object->unk_24, object->unk_25));
    object->unk_26 = room_id;

    if (actor_data->unk_6D > 0) {
        if (((u32)actor_data->flags1C) & 0x20) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (*(u16 *)&object->unk_24 == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_801717F8(actor, position, object, actor_data);
            return;
        }
        if (!(actor_data->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(actor_data,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172280(actor, position, object, 0) << 16) == 0) {
                return;
            }
            action_state = actor_data->unk_46 | 0x4000;
            actor_data->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_801717F8(actor, position, object, actor_data);
                return;
            }
        }

        action_state = actor_data->unk_46 & 0x3FFF;
        {
            u32 idx = action_state - 1;
            switch (idx) {

            case 7:
            case 8:
                if ((update_actor_animation_behavior_and_facing(actor, position, object, actor_data) << 16) != 0) {
                    return;
                }
                func_80172168(actor, position, object, actor_data);
                return;

            case 4:
            case 5:
            case 6:
            {
                EntityRec *player;
                s16 facing;

                facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(object->unk_24),(s16)(object->unk_25),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                    &distance));
                player = D_800814A8;
                actor_data->facing = facing;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, position, object, ((u8 *)D_80174C34), ((void *)update_actor_behavior_and_effect));
                    return;
                }
            }

            case 11:
                update_actor_status_and_food(actor_data);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, position, object, ((u8 *)D_80174C34), ((void *)update_actor_behavior_and_effect));
                return;

            default:
                func_801717F8(actor, position, object, actor_data);
                return;
            }
        }
    }

    if (!(((u32)actor_data->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_data->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        object->unk_24, object->unk_25,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(object->unk_24),(s16)(object->unk_25),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (object->flags & 0x40) {
        return;
    }

    anim_table = ((u8 *)D_80174C3C);
    if ((object->frameTable != anim_table) &&
        (object->frameTable != ((u8 *)D_80174C34))) {
        object->frameTable = anim_table;
        select_sprite_entry(object,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = 1;
    } else if (object->flags & 0x6000) {
        s16 anim_timer = ((Rec_func_800A9E70_arg0 *)actor)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = anim_timer;
        if (anim_timer < 0) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = (rand() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_AA < 2) {
            object->frameTable = ((u8 *)D_80174C3C);
        } else {
            object->frameTable = ((u8 *)D_80174C34);
        }
        select_sprite_entry(object,
            ((u8 *)object->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
    }

    if (!resolve_record_orientation_or_fallback(object->source, object, effect_offset, 1)) {
        return;
    }
    if (object->frameTable != ((u8 *)D_80174C3C)) {
        return;
    }

    {
        void *effect;
        void *sprite;
        void *tint;
        u8 *sprite_data;

        effect = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
        ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_pv.v = effect;
        object = effect;
        if (object == 0) {
            return;
        }
        register_node(object, project_sprite_chain);
        tint = (void *)0x00808080;
        ((ObjectNodeHeader *)object)->unk_10 = ((u8 *)D_800D79B0);
        ((EntityRec *)((ObjectNodeHeader *)object)->unk_08)->x.w.i =
            ((u16)position->x.w.i) + effect_offset[0];
        ((EntityRec *)((ObjectNodeHeader *)object)->unk_08)->y.w.i =
            ((u16)position->y.w.i) + effect_offset[1];
        ((EntityRec *)((ObjectNodeHeader *)object)->unk_08)->z.w.i =
            ((u16)position->z.w.i) + effect_offset[2];
        sprite = ((ObjectNodeHeader *)object)->unk_0C;
        sprite_data = ((u8 *)D_800DEA68);
        ((EntityRec *)((ObjectNodeHeader *)object + 1))->unk_9B = 0;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_1E = 0xC00;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_1C = 0xC00;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_0C = tint;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_00 = sprite_data;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_14 |= 0xC;
        {
            s32 anim_data = ((R08_80170E7C_S_80170E7C_8 *)sprite_data)->unk_04;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_04 = 0;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_05 = 0;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_08 = anim_data;
        }
    }
}

