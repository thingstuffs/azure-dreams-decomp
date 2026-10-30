#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/audio_commands.h"
#include "dungeon/actor/motion.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Dragon actor spawning, movement, attacks, and status animation callbacks. */
#include "dungeon/monster/dragon.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "shared/tile_object.h"
#include "dungeon/level/room_flags.h"
#include "dungeon/item.h"
#include "dungeon/effect.h"
#include "dungeon/effect/screen.h"

void * (*const resource03_slot0_entry0)(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a) = spawn_mode_dependent_112_object;
void (*const resource03_slot0_entry1)(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part) = update_entity_facing_motion_and_ground;

/* Creates a Dragon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_mode_dependent_112_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 primary_bits;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_value_0a;
    s8 saved_byte_25;

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = ((u8 *)update_entity_facing_motion_and_ground);
        work->species = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value_0a;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->tile_y = saved_byte_25;
        actor = work;
        part_b->frameTable = ((u8 *)dragon_direction_frames);
        part_b->tile_x = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = primary_bits;
            work->flags1C = secondary_flags;
        } else if (kind >= 2) {
            primary_bits = work->flags14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = primary_bits;
            work->flags1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = ((u8 *)dragon_alt_direction_frames);
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = ((void *)dispatch_monster_move_attack_spell);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

/* Runs actor callbacks and updates facing, animation, movement, and ground contact. */
void update_entity_facing_motion_and_ground(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part)
{
    R03_80170A28_S_80170A28_1 *entity_base = entity;
    s16 old_state;
    s32 state_or_direction;
    s16 direction_index;
    s16 direction_copy;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    u32 unused_tail;
    R03_80170A28_EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 entity_flags;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(R03_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (R03_80170A28_EntityCallback)((void *)dispatch_monster_move_attack_spell)) {
            {
                call_self = entity;
                callback(call_self, motion, part, call_self);
            }
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_part = part;
    old_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    call_self = entity;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        R03_80170A28_EntityCallback update_callback;
        update_callback = (*(R03_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    ((R03_80170A28_EntityCallback *)D_80173CEC)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    if ((s16)old_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, part, entity);
    }

    part_flags = ((SpriteAnimationTableView *)part)->flags;
    if (!(part_flags & 0x8000)) {
        rounded_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        direction_index = state_or_direction;
        direction_copy = state_or_direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_copy) {
            if (((SpriteAnimationTableView *)part)->frame_table != 0) {
                select_indirect_table_entry(part,
                              ((SpriteAnimationTableView *)part)->frame_table[direction_copy],
                              ((SpriteAnimationTableView *)part)->frame_index);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            ((SpriteAnimationTableView *)part)->flags |= 1;
        } else {
            ((SpriteAnimationTableView *)part)->flags &= 0xFFFE;
        }
        if (!(entity_base->unk_1C & 0x20)) {
            if (!(((SpriteAnimationTableView *)part)->flags & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            ((SpriteAnimationTableView *)part)->flags |= 0x7000;
        }
        apply_monster_koyaw_data(entity_base->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((SpriteAnimationTableView *)part)->flags = new_part_flags;
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(s8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(s8 *)((u8 *)entity + 0x9D)) = (u8)(*(s8 *)((u8 *)entity + 0x9D)) + 1;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        ground_height = ((s16)sample_terrain_surface_height(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(entity_base->unk_88 - 0x20)));
        if (ground_height < 0x200) {
            base_height = (s16)entity_base->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                entity_base->unk_1C &= 0xF7FFFFFF;
            } else if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                entity_base->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            } else {
                motion->unk_14 = 0;
                entity_base->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height - entity_base->unk_88;
            }

            entity_flags = entity_base->unk_1C;
            if (entity_flags & 0x40000000) {
                entity_base->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = ((s16)sample_terrain_surface_height(
                    (((SpriteAnimationTableView *)part)->tile_x << 6) | 0x20,
                    (((SpriteAnimationTableView *)part)->tile_y << 6) | 0x20,
                    (s16)(entity_base->unk_88 - 0x20)));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    entity_base->unk_88 - ground_height;
                entity_base->unk_88 = ground_height;
            }
        } else {
            entity_base->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        entity_base->unk_1C &= 0xF7FFFFFF;
    }

    entity_base = (R03_80170A28_S_80170A28_1 *)((u8 *)entity_base + 0x88);
    motion->unk_0A =
        *(u16 *)entity_base + (*(u16 *)((u8 *)entity + 0x92));
    ((SpriteAnimationTableView *)part)->flags |= 0x40;

    return;
}

/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void dispatch_monster_move_attack_spell(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state) {
    u8 *anim_table;
    s32 room_id;
    u16 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        controller->action_id.u = 0xE;
        advance_stored_entity_path(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->mp_value.parts.whole == 0) {
        advance_actor_pending_action(controller, context, entity, actor_state);
        if (entity->frameTable != ((u8 *)dragon_alt_direction_frames)) {
            u8 *early_table = ((u8 *)dragon_reset_frames);
            void *record = entity;
            entity = (u8 *)entity + 0x2C;
            entity->unk_00 = early_table;
            select_sprite_entry(record,
                early_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & ACTOR_ASLEEP) {
        if (entity->frameTable == ((u8 *)dragon_alt_direction_frames)) {
            controller->action_id.u = 0xD;
            controller->action_phase.u = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(controller, context, entity, ((u8 *)dragon_reset_frames))) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(controller, context, entity, actor_state);
            return;
        }

        if (controller->action_id.u != 0xE) {
            u8 control_state = 0xE;

            anim_table = ((u8 *)dragon_direction_frames);
            if (entity->frameTable != anim_table) {
                (entity->frameTable) = anim_table;
                select_sprite_entry(entity,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            controller->action_id.u = control_state;
        }

        controller->action_state_flags &= 0xFFF3;
        if (actor_state->hp_delta != 0) {
            if (begin_ready_actor_directional_action(controller, context, entity, ((u8 *)dragon_frame_set))) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(controller, context, entity, actor_state);
            update_dragon_parent_motion(controller, context, entity, actor_state);
            return;
        }

        if ((s16)can_entity_gain_level(actor_state) != 0) {
            process_selected_actor_record(controller, context, entity, actor_state);
        }
    }

    room_id = find_active_rect_containing_point(entity->tile_x, entity->tile_y);
    entity->room_index = room_id;

    if (actor_state->pending_turn_updates > 0) {
        if (((u32)actor_state->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor_state);
            return;
        }
        if (*(u16 *)&entity->tile_x == reference_tile_object.tile_position.word) {
            advance_actor_path_with_item_search(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor_state,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)dispatch_actor_path_state_and_relink_entity(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->action_flags |= 0x4000;
            if (!(actor_state->action_flags & ACTOR_ACTION_PENDING)) {
                advance_actor_path_with_item_search(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 8:
        case 9:
            if ((s16)check_actor_transition_and_start_effect(controller, context, entity, actor_state) == 0) {
                start_directional_actor_effect(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player_controller;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag((s16)(entity->tile_x),(s16)(entity->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                    &direction_flags);
                player_controller = primary_actor_record;
                actor_state->facing = direction;
                if (player_controller->action_id.u != 0x11) {
                    update_actor_status_and_mp(actor_state);
                    return;
                }
                begin_actor_spell_action(controller, context, entity, ((u8 *)D_80173CCC), ((void *)dispatch_monster_move_attack_spell));
                return;
            }
        case 12:
            update_actor_status_and_mp(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(controller, context, entity, ((u8 *)D_80173CCC), ((void *)dispatch_monster_move_attack_spell));
            return;
        default:
            break;
        }

        advance_actor_path_with_item_search(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((s16)test_neighbor_position_relation(entity->tile_x,
                    entity->tile_y, reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y) != 0) {
                    actor_state->facing = get_rounded_facing_and_rounding_flag((s16)(entity->tile_x),(s16)(entity->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &direction_flags);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (entity->flags & 0x40) {
        return;
    }
    anim_table = ((u8 *)dragon_direction_frames);
    if (entity->frameTable == anim_table) {
        return;
    }
    (entity->frameTable) = anim_table;
    select_sprite_entry(entity,
        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}

/* Advances one stored path step, updates occupied tiles and facing, and selects the movement animation and
 * delay. */
void advance_stored_entity_path(void *controller, ObjectPosition *context, void *entity, void *path_state)
{
    ActorRecord *path_actor = controller;
    R03_8017139C_S_8017139C_0 *state = path_state;
    s32 move_flags;
    s16 direction;
    s16 move_result;
    s16 x;
    s32 y;
    s32 control_flags;

    if (state->unk_71.s <= 0) {
        return;
    }

    if (state->unk_71.u <= state->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != ((u8 *)dragon_frame_set_5)) {
        (*(u8 **)((u8 *)entity + (0x2C))) = ((u8 *)dragon_frame_set_5);
        select_sprite_entry(
            entity,
            ((u8 *)dragon_frame_set_5)[((g_game_work.view.camera_rotation.parts.viewAngle + state->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (state->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    direction = ((s16)get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((ActorStatusBytesView *)((u8 *)state + state->unk_8A.s))->path_x,
        ((ActorStatusBytesView *)((u8 *)state + state->unk_8A.s))->path_y,
        &path_actor->action_state_flags));
    move_result = ((s16)check_movement_clearance_and_height(direction, entity, state, 0x20));

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((ActorStatusBytesView *)((u8 *)state + state->unk_8A.s))->path_x;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((ActorStatusBytesView *)((u8 *)state + state->unk_8A.s))->path_y;
    state->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (state->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    state->unk_2A = direction;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            copy_display_orientation_state(controller, context, entity, state);
        } else {
            ((R03_8017139C_S_8017139C_2 *)controller)->unk_9A = 0xF;
        }
    } else {
        control_flags = ((R03_8017139C_S_8017139C_2 *)controller)->unk_98;
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_9A = 0xF;
        control_flags &= ~8;
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_98 = control_flags;
    }
    ((R03_8017139C_S_8017139C_2 *)controller)->unk_8C = 0;
    state->unk_1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 0;
        return;
    }

    ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 8;
    {
        s32 step_count = state->unk_71.u;
        if (step_count > 0) {
            ((R03_8017139C_S_8017139C_2 *)controller)->unk_96 = 8 / step_count;
        }
    }
}

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void advance_actor_path_with_item_search(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data) {
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (actor_data->unk_12 >= 2 ||
            (s16)check_actor_transition_and_start_effect(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y));
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(blocker_sprite->tile_x),(s16)(blocker_sprite->tile_y),
                    &move_data->action_state_flags));
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y),(s16)(actor_data->facing)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_x == (u16)target_x &&
                    position_data->tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = &move_data->action_state_flags;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                actor_data->facing = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                              &move_data->action_state_flags);
            }
        }
    } else if ((s8)position_data->room_index >= 0 &&
               dungeon_rooms[(s8)position_data->room_index].flags & ROOM_HOLY_BEAM) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                      &move_data->action_state_flags);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y),(s16)(actor_data->facing));
        blocker = (ActorRecord *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)((s16)get_actor_height_difference(blocker, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    (actor_data->facing >> 9) & 0xFFFF,(s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), &move_data->action_state_flags));
            if (((s16)test_neighbor_position_relation(
                    position_data->tile_x, position_data->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            (actor_data->facing >> 9) & 0xFFFF,(s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                          &move_data->action_state_flags);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = move_data->action_state_flags;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_x =
                position_data->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_y =
                position_data->tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_x, position_data->tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = ((u16)actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_x += *x_step;
                position_data->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)(position_data->tile_x),(s16)(position_data->tile_y),(u16)((actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&position_data->tile_x) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (position_data->tile_x << 6) | 0x20,
        (position_data->tile_y << 6) | 0x20,(s16)((s16)(actor_data->ground_height - 0x20))));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}

/*
 * Sets action state 0x10, clears its tick, and selects a camera-relative eight-way sprite entry
 * from D_80173C8C.
 */
void copy_display_orientation_state(void *object, ObjectPosition *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80173C8C);
    ((SpriteFrameState *)display)->frameTable = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 check_actor_transition_and_start_effect(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor) {
    ActorRecord *neighbor;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    neighbor = probe_directional_neighbor(actor, sprite_arg->tile_x,
                           sprite_arg->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, neighbor) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(neighbor, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->action_id.s = 0x11;
        action_state->action_phase.s = 0;
        action_state->unk_8C.run = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite_arg->frameTable = ((u8 *)dragon_direction_frames);
        select_sprite_entry(sprite_arg, (((u8 *)dragon_direction_frames))[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}

/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void start_directional_actor_effect(ActorRecord *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->action_id.s = 0x11;
            action_state->unk_8C.run = 0;
            action_state->action_phase.s = 0;
            (*(s32 **)((u8 *)sprite + 0x2C)) = ((u8 *)dragon_direction_frames);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)dragon_direction_frames)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 dispatch_actor_path_state_and_relink_entity(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        advance_actor_path_with_item_search(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R03_8017207C_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        advance_actor_path_with_item_search(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R03_8017207C_S_80172628_0 *)entity)->unk_71 = (u8) (((R03_8017207C_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R03_8017207C_S_80172628_0 *)entity)->unk_71 = (u8) (((R03_8017207C_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R03_8017207C_S_80172628_0 *)entity)->unk_46 = (u16) (((R03_8017207C_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

/*
 * On completed movement, spends MP and advances status timers, resuming monster dispatch only
 * after a positive signed floor-trap result. Clears both action halfwords under flag 0x80 during
 * movement or after an accepted trap check. /
 */
void finish_actor_tile_move_and_check_trap(R03_801721C0_S_801721C0_0 *object, void *motion, void *check_data, void *target) {
    if (update_actor_movement_to_tile(object, motion, check_data, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(check_data, target) << 0x10) > 0) {
            object->unk_8C = ((void *)dispatch_monster_move_attack_spell);
            if (g_dungeon_status.flags & 0x80) {
                object->unk_90.at02.v = 0;
                object->unk_90.at00.v = 0;
            }
        }
    } else {
        if (g_dungeon_status.flags & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}

/* Jumps to the destination tile, updates landing animation, spends MP, and checks for a floor trap. */
void complete_actor_jump_to_destination(void *jump, void *motion, void *map_entity, void *actor) {
    u16 facing_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((R03_80172258_S_80172258_0 *)jump)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)map_entity)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)map_entity)->frameTable = ((u8 *)dragon_frame_set_2);
        select_sprite_entry(
            map_entity,
            ((u8 *)dragon_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172258_S_80172258_0 *)jump)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFF20000;
        ((ActorRecord *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((R03_80172258_S_80172258_0 *)jump)->unk_A0 = 0;
        ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;

    case 1:
        frames_left = ((R03_80172258_S_80172258_0 *)jump)->unk_96.s;
        ((R03_80172258_S_80172258_0 *)jump)->unk_90 -= ((R03_80172258_S_80172258_0 *)jump)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)map_entity)->tile_x << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)map_entity)->tile_y << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((R03_80172258_S_80172258_0 *)jump)->unk_96.s;
            }
            ((R03_80172258_S_80172258_0 *)jump)->unk_A0 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x38000;
        }
        ((R03_80172258_S_80172258_0 *)jump)->unk_90 += ((R03_80172258_S_80172258_0 *)jump)->unk_A0;
        if (((R03_80172258_S_80172258_0 *)jump)->unk_96.s < 2) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_90 = 0;
            ((R03_80172258_S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= ACTOR_GROUNDED;
            ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;
        }

    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & ACTOR_GROUNDED) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->tile_x, ((SpriteFrameState *)map_entity)->tile_y);
            ((SpriteFrameState *)map_entity)->frameTable = ((u8 *)dragon_frame_set_3);
            select_sprite_entry(
                map_entity,
                ((u8 *)dragon_frame_set_3)[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;
        }
    default:
        break;
    }

    next_timer = ((R03_80172258_S_80172258_0 *)jump)->unk_96.u - 1;
    ((R03_80172258_S_80172258_0 *)jump)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->tile_x, ((SpriteFrameState *)map_entity)->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {
            u32 count_unsigned;
            s32 count_signed;

            count_signed = g_dungeon_status.activity_counts.parts.pending_movement_count;
            count_unsigned = ((u16)g_dungeon_status.activity_counts.parts.pending_movement_count);

            if (count_signed != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count = count_unsigned - 1;
            }
        }

        actor_flags = ((u32)((ActorRecord *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING) {
                ((ActorRecord *)actor)->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((ActorRecord *)actor)->facing = ((s16)get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)map_entity)->tile_x, ((SpriteFrameState *)map_entity)->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_distance));
            }
        }

finish:
        if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
            on_actor_status_updated(actor);
        }
    }
}

/*
 * Runs update_linked_actor_motion and installs dispatch_monster_move_attack_spell only when it
 * succeeds and the signed floor-trap check returns positive.
 */
void update_dragon_linked_motion(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = dispatch_monster_move_attack_spell;
        }
    }
}

/* Chooses an attack animation with an optional sprite effect, applies damage, spends MP, and restores
 * movement. */
void advance_actor_attack_and_resolve_damage(void *action, void *transform, void *sprite, ActorRecord *actor)
{
    s32 state;
    void *allocated_effect;
    void *effect = 0;
    SpriteFrameState *effect_sprite;
    R03_80172620_Copy24 *effect_transform;

    ((R03_80172620_S_80172620_0 *)action)->unk_96--;
    state = ((R03_80172620_S_80172620_0 *)action)->phase;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R03_80172620_S_80172620_0 *)action)->phase = 0xFF;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            return;
        }

        if (rand() & 3) {
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)dragon_frame_set_4);
            (*(s32 *)((u8 *)action + 0xA4)) = 0;
            select_sprite_entry(sprite,
                (*(u8 **)&((SpriteFrameState *)sprite)->frameTable)
                    [((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R03_80172620_S_80172620_0 *)action)->phase = 3;
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)dragon_frame_set_1);
        select_sprite_entry(sprite,
            ((u8 *)dragon_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->phase++;
        return;

    case 1:
        if ((((SpriteFrameState *)sprite)->unk_04 == 2) &&
            (((SpriteFrameState *)sprite)->flags & 0x1000)) {
            allocated_effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
            ((R03_80172620_S_80172620_0 *)action)->unk_A4.s = allocated_effect;
            effect = allocated_effect;
            if (effect != 0) {
                s32 sprite_link;
                s32 sprite_data;

                register_node(effect, project_sprite_chain);
                ((R03_80172620_S_80172620_3 *)effect)->unk_10 = ((u8 *)effect_update_tag);
                effect_transform = ((R03_80172620_S_80172620_3 *)effect)->unk_08;
                *effect_transform = *(R03_80172620_Copy24 *)transform;
                ((R03_80172620_S_80172620_3 *)effect)->unk_BB = 0;
                ((R03_80172620_S_80172620_3 *)effect)->unk_4A = ((u16)actor->facing);

                effect_sprite = ((R03_80172620_S_80172620_3 *)effect)->unk_0C;
                sprite_link = ((SpriteFrameState *)sprite)->animation_resource;
                effect_sprite->scale_y = 0x1000;
                effect_sprite->scale_x = 0x1000;
                effect_sprite->animation_resource = sprite_link;
                effect_sprite->flags = ((SpriteFrameState *)sprite)->flags;
                effect_sprite->clut = ((SpriteFrameState *)sprite)->clut;
                sprite_data = ((SpriteFrameState *)sprite)->color.word;
                effect_sprite->frameTable = ((u8 *)D_80173CB4);
                effect_sprite->color.word = sprite_data;
                select_sprite_entry(effect_sprite,
                    ((u8 *)D_80173CB4)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }

        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80173CAC);
        select_sprite_entry(sprite,
            ((u8 *)D_80173CAC)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172620_S_80172620_0 *)action)->phase++;
        return;

    case 2:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            R03_80172620_S_80172620_5 *active_effect;

            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)dragon_frame_set_4);
            select_sprite_entry(sprite,
                ((u8 *)dragon_frame_set_4)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            active_effect = ((R03_80172620_S_80172620_0 *)action)->unk_A4.s;
            if (active_effect != 0) {
                active_effect->unk_BB = 0xFF;
                ((R03_80172620_S_80172620_0 *)action)->unk_A4.u = 0;
            }
            ((R03_80172620_S_80172620_0 *)action)->phase++;
        }

    case 3:
        if (((((SpriteFrameState *)sprite)->unk_04 == 2) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            play_sound_if_enabled(0x808);
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            ((R03_80172620_S_80172620_0 *)action)->phase = 0xFF;
        }
        return;

    case 0xFF:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(transform,(u8)((SpriteFrameState *)sprite)->tile_x,(u8)((SpriteFrameState *)sprite)->tile_y);
        spend_actor_mp(actor, 0x180);
        ((R03_80172620_S_80172620_0 *)action)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        } else {
            (*(void **)actor_update_node_cursor) = (u8 *)actor - 0x20;
        }

        return;
    }
}

/* Starts a targeted spell with a two-row effect, then restores movement and status after the animation. */
void finish_timed_actor_movement(void *action_state, void *transform, void *sprite, ActorRecord *actor)
{
    u16 position[4];
    u8 *motion;
    s16 use_player_target;
    SpriteLinkPrefixView *target;
    s32 delay;
    MovingTile *action_status;

    use_player_target = 0;
    switch (((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 7:
                use_player_target = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player_target = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player_target = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 player_target = use_player_target;
                if (player_target != 0) {
                    target = primary_actor_record;
                    actor->target = target;
                    action_status = (u8 *)target[-1].sprite;
                    actor->target_tile_x = action_status->tile_x;
                    actor->target_tile_y = action_status->tile_y;
                } else if (item_action_definitions[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_status = (u8 *)target[-1].sprite;
                        actor->target_tile_x = action_status->tile_x;
                        actor->target_tile_y = action_status->tile_y;
                    }
                } else {
                    actor->target =
                        scan_actor_along_heading(actor,(u8)((SpriteFrameState *)sprite)->tile_x,(u8)((SpriteFrameState *)sprite)->tile_y,(s16)(actor->facing), 0x10);
                    actor->target_tile_x = abs(actor->target_tile_x);
                    actor->target_tile_y = abs(actor->target_tile_y);
                }
            }
            position[0] = ((u16)((EntityRec *)transform)->x.w.i);
            position[1] = ((u16)((EntityRec *)transform)->y.w.i);
            position[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)create_actor_spell_effect(actor, motion,(s16)(use_player_target), (u8 *)action_state + 0x98);
            if (transform == 0) {
                return;
            }
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(position,(s16)((*motion - 1) % 3));
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)((SpriteFrameState *)sprite)->tile_x,(u8)((SpriteFrameState *)sprite)->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4.value + 2)) = (*(u16 *)((u8 *)primary_actor_record + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_8C = ((u8 *)dispatch_monster_move_attack_spell);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((SpriteFrameState *)sprite)->unk_04 == 4 && (((SpriteFrameState *)sprite)->flags & 0x1000))
            ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = 0x3;
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_98 |= 0x80;
        }
        delay = ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 - 1;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = delay;
        if ((s16)delay <= 0) {
            ((R03_80172A24_S_80172A24_0 *)action_state)->unk_96 = 0;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        }
        if ((((SpriteFrameState *)sprite)->flags & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)((SpriteFrameState *)sprite)->tile_x,(u8)((SpriteFrameState *)sprite)->tile_y);
        {
            u8 *direction_table = ((u8 *)dragon_direction_frames);

            if (*(u8 **)&((SpriteFrameState *)sprite)->frameTable != direction_table) {
                ((SpriteFrameState *)sprite)->frameTable = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_status = (u8 *)&g_dungeon_status.turn_scale;
        if (((R03_80172A24_S_80172A24_7 *)action_status)->unk_0C != 0) {
            return;
        }
        ((R03_80172A24_S_80172A24_7 *)action_status)->unk_0A = ((R03_80172A24_S_80172A24_7 *)action_status)->unk_0A - 1;
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((R03_80172A24_S_80172A24_0 *)action_state)->unk_8C = ((u8 *)dispatch_monster_move_attack_spell);
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    }
}

/* Applies a value change and knockback, decelerates the actor, then recenters it and restores movement. */
void slow_directional_movement_to_tile(R03_80172F14_S_80172F14_1 *controller, ObjectPosition *motion, SpriteFrameState *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 speed_limit;
    s32 tracked_object;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;

    switch (controller->phase) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + direction * 2) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + direction * 2) << 19;
        controller->phase++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, entity, D_80173CC4);
            return;
        }
        if (entity->flags & 0x8000) {
            controller->timer.s = 0;
            controller->phase = 2;
            return;
        }

        timer = 5;
        if (((EntityRec *)source)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        }
        controller->timer.s = timer;

        {
            s32 velocity = motion->velocity_x;
            motion->velocity_x = velocity - velocity / 4;
        }
        {
            s32 velocity = motion->velocity_y;
            motion->velocity_y = velocity - velocity / 4;
        }
                        /* fall through */

    case 1:
        speed_limit = 0x7FFF;
        {
            s32 velocity = motion->velocity_x;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->velocity_x = velocity -
                    (*(s16 *)((u8 *)((s8 *)dir_step_x) + direction * 2) << 15);
            }
        }
        {
            s32 velocity = motion->velocity_y;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->velocity_y = velocity -
                    (*(s16 *)((u8 *)((s8 *)dir_step_y) + direction * 2) << 15);
            }
        }

        if (controller->timer.s > 0) {
            controller->timer.s = controller->timer.u - 1;
        } else {
            if (entity->flags & 0x6000) {
                controller->timer.s = 0;
            }

            if (((EntityRec *)source)->unk_28 != 0) {
                {
                    s32 tile_pos = entity->tile_x << 6;
                    s32 current_pos = motion->x.w.i - 0x20;

                    motion->velocity_x = (tile_pos - current_pos) << 15;
                }
                {
                    s32 tile_pos = entity->tile_y << 6;
                    s32 current_pos = motion->y.w.i - 0x20;

                    motion->velocity_y = (tile_pos - current_pos) << 15;
                }
            } else {
                motion->velocity_x = 0;
                motion->velocity_y = 0;
            }
        }

        if (controller->timer.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            begin_actor_display_action(controller, motion, entity, D_80173CC4);
            return;
        }
        controller->timer.s = 8;
        controller->phase++;
        return;

    case 2:
        if (controller->timer.s != 0) {
            {
                s32 tile_pos = entity->tile_x << 6;
                s32 current_pos = motion->x.w.i - 0x20;

                motion->velocity_x = (tile_pos - current_pos) << 16;
            }
            {
                s32 tile_pos = entity->tile_y << 6;
                s32 current_pos = motion->y.w.i - 0x20;

                motion->velocity_y = (tile_pos - current_pos) << 16;
            }
        }

        timer = controller->timer.u - 1;
        controller->timer.s = timer;
        if ((timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->tile_x,
                      entity->tile_y);

        tracked_object = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_object == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_object & 0x7FFFFFFF;
        }
        controller->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        return;

    default:
        return;
    }
}

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void remove_defeated_dragon(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

/* Runs the shared hop and shrink sequence for the actor with the supplied callback arguments. */
void shrink_hopping_dragon(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_dragon_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

/*
 * Runs update_actor_hop_and_grow and installs dispatch_monster_move_attack_spell when it returns
 * nonzero.
 */
void grow_hopping_dragon(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void update_actor_status_and_restore_handler(void *in_controller, ObjectPosition *in_context, void *sprite, ActorRecord *in_actor) {
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B;
    switch (state) {
    case 0:
        if (((R03_80173358_S_80173358_1 *)sprite)->unk_14 & 0xE000) {
            u8 *direction_anims;
            DungeonGlobalStatus *system_base;

            direction_anims = ((u8 *)dragon_alt_direction_frames);
            (*(void **)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R03_80173358_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B++;
        }
        return;

    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &g_dungeon_status;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((R03_80173358_S_80173358_2 *)actor)->unk_64 != 0) &&
                (begin_ready_actor_directional_action(in_controller, context, sprite, 0) != 0)) {
                return;
            }

            if (((R03_80173358_S_80173358_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_controller, context, sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((R03_80173358_S_80173358_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_controller, context, sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_controller, context, sprite, actor);
                update_dragon_parent_motion(in_controller, context, sprite, actor);
                return;
            }

            if (((R03_80173358_S_80173358_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &reference_tile_object;
                coordinate = ((R03_80173358_S_80173358_1 *)sprite)->unk_26;
                if ((((coordinate == origin->room_index) &&
                    (coordinate >= 0)) ||
                    (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, STATUS_SLEEP);
                }
            }

            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = ((u8 *)D_80173CE4);
            (*(void **)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R03_80173358_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        sprite = (u8 *)sprite + 0x14;
        if (!(*(u16 *)sprite & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)++;
            ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B++;
            return;
        }
        break;

    case 2:
        if (!(((R03_80173358_S_80173358_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
        }

        break;
    default:
        return;
    }
    ((R03_80173358_S_80173358_2 *)actor)->unk_1C &= ~ACTOR_ASLEEP;
    in_controller = (u8 *)in_controller + 0x8C;
    *(void **)in_controller = ((u8 *)dispatch_monster_move_attack_spell);
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void wait_for_dragon_mp(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    s32 state;

    state = controller->action_phase.u;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(sprite->flags & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)dragon_alt_direction_frames);
        sprite->frameTable = direction_anims;
        select_sprite_entry(sprite,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        controller->action_phase.u++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp_value.parts.whole != 0) {

            sprite->frameTable = ((u8 *)dragon_reset_frames);
            select_sprite_entry(sprite,
                ((u8 *)dragon_reset_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            controller->action_phase.u++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            update_dragon_parent_motion(controller, context, sprite, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp_value.parts.whole == 0) {
            return;
        }

        sprite->frameTable = ((u8 *)dragon_reset_frames);
        select_sprite_entry(sprite,
            ((u8 *)dragon_reset_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        controller->action_phase.u++;
    }
        break;
    case 2:
        if (sprite->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~0x208;
            controller->unk_8C.address = ((void *)dispatch_monster_move_attack_spell);
        }

        return;
    }
}

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_dragon_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object) {
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C.handler = ((u8 *)dispatch_monster_move_attack_spell);
            return;
        }
    } else if (entity->frameTable == ((u8 *)dragon_alt_direction_frames) &&
               !(map_object->flags1C & 0x208)) {
        entity->frameTable = ((u8 *)dragon_frame_set_5);
        select_sprite_entry(entity,(s16)(((u8 *)dragon_frame_set_5)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->facing + 0x100) >> 9) & 7]),(s16)(0));
    }
}

/*
 * Runs update_thrown_actor_travel and installs dispatch_monster_move_attack_spell only when it
 * succeeds and the signed floor-trap check returns positive.
 */
void update_thrown_dragon(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = dispatch_monster_move_attack_spell;
        }
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs dispatch_monster_move_attack_spell when it
 * returns nonzero.
 */
void settle_dragon_on_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs update_spinning_actor_fall and installs dispatch_monster_move_attack_spell when it returns
 * nonzero.
 */
void fade_entity_colors_to_neutral(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}

/* Runs update_actor_fade_in and installs dispatch_monster_move_attack_spell when it returns nonzero. */
void fade_in_dragon(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs resolve_actor_floor_trap_once and installs dispatch_monster_move_attack_spell when it
 * returns positive.
 */
void resolve_dragon_floor_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs propagate_actor_action_flag and installs dispatch_monster_move_attack_spell when it returns
 * positive.
 */
void propagate_dragon_action_flag(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->unk_8C.handler = dispatch_monster_move_attack_spell;
    }
}
