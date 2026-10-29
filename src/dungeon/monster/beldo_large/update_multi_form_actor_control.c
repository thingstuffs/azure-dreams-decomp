#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "m2c_compat.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

#include "engine/graphics/select_sprite_entry_api.h"
#include "slus.h"
#include "sdk/libc.h"
#include "dungeon/item.h"
struct ActorRecord; s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(struct ActorRecord *);
void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
s32 advance_actor_pending_action(void *, void *, void *, void *);
struct Rec_func_800A9E70_arg0; struct Rec_func_800AA258_arg2; void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
void advance_multi_form_turn_path(ActorRecord *actor, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *movement);
void advance_actor_movement_step(u8 *, ObjectPosition *, u8 *, u8 *);
struct Rec_D_80082E80; struct Rec_func_800A9E70_arg0; s32 try_actor_attack(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *target, ActorRecord *actor);
void start_actor_attack(void *, ObjectPosition *, s32, void *);
struct Rec_func_800A9E70_arg0; s32 resolve_actor_movement_action(struct Rec_func_800A9E70_arg0 *, ObjectPosition *, s32, s32);
void update_multi_form_actor_movement(ActorRecord *object, ObjectPosition *update_param, SpriteFrameState *state, ActorRecord *input);
struct Rec_func_800A9E70_arg0; void complete_actor_facing_action(struct Rec_func_800A9E70_arg0 *, ObjectPosition *, s32, struct ActorRecord *);
struct Rec_func_800A9E70_arg0; void start_actor_directional_action(struct Rec_func_800A9E70_arg0 *, ObjectPosition *, SpriteFrameState *, struct ActorRecord *);
s32 advance_actor_effect_sequence_2();
extern u8 beldo_large_frame_set_2;
extern u8 beldo_large_frame_set_5;
extern u8 beldo_large_frame_set_1;
extern u8 beldo_large_frame_set_3;
extern u8 beldo_large_frame_set_6[];
extern u8 beldo_large_frame_set_17[];
extern u8 beldo_large_frame_set_18[];
extern u8 D_801739F8[];
extern u8 beldo_large_frame_set_19[];
extern u8 D_80173A08[];
extern u8 D_80173A10[];
extern u8 D_80173A18[];
extern u8 beldo_large_frame_set_12;
extern u8 beldo_large_frame_set_9;
extern u8 beldo_large_frame_set_13[];
extern u8 beldo_large_frame_set_4[];

/* Updates dungeon actor actions, facing, and idle animations. */
/* Dispatches movement, attacks, and spells for four actor forms, with separate idle frames and timed idle
 * gestures. */
void update_multi_form_actor_control(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    Rec_func_800A9E70_arg0 *pose_actor;
    u16 distance;
    u8 *idle_table;
    u8 *pose2_table;
    u8 *pose3_table;
    unsigned long table_index;
    u8 *next_table;
    u8 *current_table;
    s32 entity_flags;
    s32 action_id;
    s8 room_id;
    u16 action_flags;
    u16 pose2_idle_ticks;
    u16 pose2_anim_ticks;
    u16 pose3_idle_ticks;
    u16 pose3_anim_ticks;
    s32 inactive_pose;
    s32 flagged_pose;
    s32 anim_state;
    s32 active_pose;
    s32 action_pose;
    s32 idle_pose;
    u32 clear_mask;
    s32 state_changed;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 0xEU;
        advance_multi_form_turn_path(actor, context, sprite, entity);
        if (actor->unk_B0.bytes[0] != 1) {
            return;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = (u8) (((Rec_func_800A9E70_arg0 *)actor)->unk_AD + 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        return;
    }
    if (actor->unk_B0.bytes[0] == 1) {
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_AD != 0) {
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - ((Rec_func_800A9E70_arg0 *)actor)->unk_AD);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = 0U;
        }
    }
    if (entity->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        inactive_pose = actor->unk_AC.byte;
        switch (inactive_pose) {
        case 0xD:
            if (*(s32 **)&sprite->frameTable == (s32 *)((u8 *)&beldo_large_frame_set_13 + 8)) {
                return;
            }
            (sprite->frameTable) = (s32 *)((u8 *)&beldo_large_frame_set_9 + 0x68);
            table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)(s32 *)((u8 *)&beldo_large_frame_set_9 + 0x68);
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        case 0xE:
            if (*(s32 **)&sprite->frameTable == (s32 *)((u8 *)&beldo_large_frame_set_9 + 0x70)) {
                return;
            }
            (sprite->frameTable) = &beldo_large_frame_set_13;
            table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)&beldo_large_frame_set_13;
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        case 0xF:
            if (*(s32 **)&sprite->frameTable == &beldo_large_frame_set_4) {
                return;
            }
            (sprite->frameTable) = (s32 *)((u8 *)&beldo_large_frame_set_19 + 0xC0);
            table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)(s32 *)((u8 *)&beldo_large_frame_set_19 + 0xC0);
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        }
        return;
    }
    if (entity->flags1C & ACTOR_ASLEEP) {
        flagged_pose = actor->unk_AC.byte;
        switch (flagged_pose) {
        case 0xD:
            if (*(s32 **)&sprite->frameTable != &beldo_large_frame_set_4) {
                break;
            }
            clear_mask = 0xFFFB0000U;
            state_changed = 1;
            actor->action_id.u = flagged_pose;
            goto block_32;
        case 0xE:
            if (*(s32 **)&sprite->frameTable == &beldo_large_frame_set_4) {
                goto block_31;
            }
            break;
        case 0xF:
            if (*(s32 **)&sprite->frameTable != &beldo_large_frame_set_4) {
                break;
            }
block_31:
            clear_mask = 0xFFFB0000U;
            actor->action_id.u = 0xDU;
            state_changed = 1;
block_32:
            actor->action_phase.s = (s8)state_changed;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags1C = (s32) (entity->flags1C & (clear_mask | 0xFFFFU));
            return;
        default:
            goto block_37;
        }
        if (reset_actor_action_state(actor, context, sprite, (u8 *)(&beldo_large_frame_set_13)) != 0) {
            return;
        }
    }
block_37:
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }
        {
            s16 idle_state = 0xE;
            anim_state = actor->action_id.u;
            if (anim_state != idle_state) {
                anim_state = actor->unk_AC.byte;
                switch (anim_state) {
                case 0:
                    if (*(u8 **)&sprite->frameTable != &beldo_large_frame_set_2) {
                        (sprite->frameTable) = &beldo_large_frame_set_2;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &beldo_large_frame_set_2), 0);
                    }
                    break;
                case 1:
                    if (*(u8 **)&sprite->frameTable != &beldo_large_frame_set_5) {
                        (sprite->frameTable) = &beldo_large_frame_set_5;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &beldo_large_frame_set_5), 0);
                    }
                    break;
                case 2:
                    if (*(u8 **)&sprite->frameTable != &beldo_large_frame_set_1) {
                        (sprite->frameTable) = &beldo_large_frame_set_1;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &beldo_large_frame_set_1), 0);
                    }
                    break;
                case 3:
                    if (*(u8 **)&sprite->frameTable != &beldo_large_frame_set_3) {
                        (sprite->frameTable) = &beldo_large_frame_set_3;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &beldo_large_frame_set_3), 0);
                    }
                    break;
                }
                actor->action_id.u = 0xEU;
                actor->unk_9E.u = 0U;
                actor->unk_A0.parts.low = (s16) ((rand() & 0x1F) + 0xF);
            }
        }
        actor->action_state_flags = (u16) (actor->action_state_flags & 0xFFF3);
        if (entity->hp_delta != 0) {
            active_pose = actor->unk_AC.byte;
            switch (active_pose) {
            case 0:
                if (begin_ready_actor_directional_action(actor, context, sprite, beldo_large_frame_set_19) != 0) {
                    return;
                }
                break;
            case 1:
                if (begin_ready_actor_directional_action(actor, context, sprite, D_80173A08) != 0) {
                    return;
                }
                break;
            case 2:
                if (begin_ready_actor_directional_action(actor, context, sprite, D_80173A10) != 0) {
                    return;
                }
                break;
            case 3:
                if (begin_ready_actor_directional_action(actor, context, sprite, D_80173A18) != 0) {
                    return;
                }
                break;
            }
        }
        if (entity->flags1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            update_multi_form_actor_movement(actor, context, sprite, entity);
            return;
        }
        if ((can_entity_gain_level(entity) << 0x10) != 0) {
            if (((s32)g_dungeon_status.active_actor) != entity) {
                return;
            }
            if ((g_dungeon_status.pending_display_owner) != 0) {
                return;
            }
            if ((s16) ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) >= 2) {
                return;
            }
            if (g_dungeon_status.flags & 8) {
                return;
            }
            entity->experience = 0;
            g_dungeon_status.active_actor = 0;
        }
    }
    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;
    if (entity->pending_turn_updates > 0) {
        if (entity->flags1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity, (struct ActorRecord *)(((u8 *)primary_actor_record->previous_actor_header) + 0x20)) << 0x10) != 0) {
                    return;
                }
            }
            if (system_update_flags & 8) {
                advance_actor_effect_sequence_2(actor, context, sprite);
                entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
                update_actor_status_and_mp(entity);
                entity->action_flags = (u16) (entity->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
                return;
            }
            if ((resolve_actor_movement_action(actor, context, (s32)(sprite), 0) << 0x10) == 0) {
                return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
                return;
            }
        }
        action_id = entity->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_id) {
        case 8:
            if ((try_actor_attack(actor, context, sprite, entity) << 0x10) != 0) {
                return;
            }
            start_actor_attack(actor, context, (s32)(sprite), entity);
            return;
        case 9:
            complete_actor_facing_action(actor, context, (s32)(sprite), entity);
            return;
        case 10:
            start_actor_directional_action(actor, context, sprite, entity);
            return;
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 5:
        case 6:
        case 7:
        {
            s32 angle = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            ActorRecord *owner = primary_actor_record;
            entity->facing = (s16)angle;
            if (owner->action_id.u != 0x11) {
                update_actor_status_and_mp(entity);
                return;
            }
        }
        case 1:
        case 2:
        case 3:
            action_pose = actor->unk_AC.byte;
            switch (action_pose) {
            case 0:
                begin_actor_spell_action(actor, context, sprite, (u8 *)(&beldo_large_frame_set_6), &update_multi_form_actor_control);
                return;
            case 1:
                begin_actor_spell_action(actor, context, sprite, (u8 *)(&beldo_large_frame_set_17), &update_multi_form_actor_control);
                return;
            case 2:
                begin_actor_spell_action(actor, context, sprite, (u8 *)(&beldo_large_frame_set_18), &update_multi_form_actor_control);
                return;
            case 3:
                begin_actor_spell_action(actor, context, sprite, (u8 *)(&D_801739F8), &update_multi_form_actor_control);
                return;
            }
            return;
        default:
            advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
            return;
        }
    }
    pose_actor = (Rec_func_800A9E70_arg0 *)actor;
    entity_flags = entity->flags1C;
    if (!(entity_flags & 0x2000)) {
        if (!(system_update_flags & 8)) {
            if (room_id < 0 || !(dungeon_rooms[room_id].flags & 2)) {
                if (!(entity_flags & 0x430)) {
                    if ((test_neighbor_position_relation(sprite->tile_x,
                        sprite->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
                        entity->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x,
                            sprite->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                    }
                }
            }
        }
    }
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    if (entity->flags1C & ACTOR_PARALYZED) {
        return;
    }
    if ((*(u16 *)0x80013714) & 8) {
        return;
    }
    idle_pose = pose_actor->unk_AC;
    switch (idle_pose) {
    case 0:
        next_table = &beldo_large_frame_set_2;
        current_table = sprite->frameTable;
        if (current_table == next_table) {
            return;
        }
        (sprite->frameTable) = next_table;
        table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)next_table;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        return;
    case 1:
        current_table = sprite->frameTable;
        next_table = &beldo_large_frame_set_5;
        if (current_table == next_table) {
            return;
        }
        (sprite->frameTable) = next_table;
        table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)next_table;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        return;
    case 2:
        pose2_table = sprite->frameTable;
        if (pose2_table != &beldo_large_frame_set_1 && pose2_table != &beldo_large_frame_set_12) {
            (sprite->frameTable) = &beldo_large_frame_set_1;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + &beldo_large_frame_set_1), 0);
            pose_actor->unk_9E.as_u16 = 0U;
            pose_actor->unk_A0.at00_s16.v = (s16) ((rand() & 0x3F) + 0x3C);
        }
        if (pose2_table == &beldo_large_frame_set_1 || *(s32 **)&sprite->frameTable == &beldo_large_frame_set_1) {
            pose2_idle_ticks = pose_actor->unk_9E.as_u16;
            pose_actor->unk_9E.as_u16 = (u16) (pose2_idle_ticks + 1);
            if ((s16) pose2_idle_ticks >= pose_actor->unk_A0.at00_s16.v) {
                (sprite->frameTable) = &beldo_large_frame_set_12;
                select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                    + &beldo_large_frame_set_12), 0);
                advance_sprite_animation_and_textures(sprite);
                pose_actor->unk_9E.as_u16 = 0U;
            }
        }
        if (*(s32 **)&sprite->frameTable != &beldo_large_frame_set_12) {
            return;
        }
        pose2_anim_ticks = pose_actor->unk_9E.as_u16;
        pose_actor->unk_9E.as_u16 = (u16) (pose2_anim_ticks + 1);
        if ((s16) pose2_anim_ticks < 0x12) {
            return;
        }
        (sprite->frameTable) = &beldo_large_frame_set_1;
        table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)&beldo_large_frame_set_1;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        pose_actor->unk_9E.as_u16 = 0U;
        pose_actor->unk_A0.at00_s16.v = (s16) ((rand() & 0x3F) + 0x3C);
        return;
    case 3:
        pose3_table = sprite->frameTable;
        idle_table = &beldo_large_frame_set_3;
        if (pose3_table != idle_table && pose3_table != &beldo_large_frame_set_9) {
            (sprite->frameTable) = idle_table;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + idle_table), 0);
            pose_actor->unk_9E.as_u16 = 0U;
            pose_actor->unk_A0.at00_s16.v = (s16) ((rand() & 0x3F) + 0x3C);
        }
        if (pose3_table == idle_table || *(s32 **)&sprite->frameTable == idle_table) {
            pose3_idle_ticks = pose_actor->unk_9E.as_u16;
            pose_actor->unk_9E.as_u16 = (u16) (pose3_idle_ticks + 1);
            if ((s16) pose3_idle_ticks >= pose_actor->unk_A0.at00_s16.v) {
                (sprite->frameTable) = &beldo_large_frame_set_9;
                select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                    + &beldo_large_frame_set_9), 0);
                advance_sprite_animation_and_textures(sprite);
                pose_actor->unk_9E.as_u16 = 0U;
            }
        }
        if (*(s32 **)&sprite->frameTable != &beldo_large_frame_set_9) {
            return;
        }
        pose3_anim_ticks = pose_actor->unk_9E.as_u16;
        pose_actor->unk_9E.as_u16 = (u16) (pose3_anim_ticks + 1);
        if ((s16) pose3_anim_ticks < 0x12) {
            return;
        }
        (sprite->frameTable) = &beldo_large_frame_set_3;
        table_index = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)&beldo_large_frame_set_3;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        pose_actor->unk_9E.as_u16 = 0U;
        pose_actor->unk_A0.at00_s16.v = (s16) ((rand() & 0x3F) + 0x3C);
        return;
    }
}
