#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/monster/troll.h"
#include "engine/graphics.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 check_entity_relation();                     /* extern */
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);                           /* extern */
s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);                  /* extern */
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);       /* extern */
s32 can_entity_gain_level(void *entity);                          /* extern */
void update_actor_status_and_mp(ActorRecord *entity);                      /* extern */
void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in); /* extern */
s32 begin_ready_actor_directional_action(); /* extern */
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor); /* extern */
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor); /* extern */
s32 reset_actor_action_state(); /* extern */
s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor); /* extern */
void begin_actor_spell_action(); /* extern */
void advance_actor_stored_path_2(ActorRecord *movement, ObjectPosition *actor_index, SpriteFrameState *actor, ActorRecord *path_state);                            /* extern */
s32 func_80173EAC(); /* extern */
void update_directional_action_display(); /* extern */
void update_actor_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_80175DF4[];
extern u8 D_80175DFC[];
extern u8 D_80175E04[];
extern u8 troll_frame_set_1[];
extern u8 troll_frame_set_2[];
extern u8 troll_frame_set_3[];
extern u8 troll_frame_set_5[];
extern u8 troll_frame_set_6[];
extern u8 troll_frame_set_7[];
extern u8 troll_kind13_direction_frames[];
extern u8 troll_kind14_direction_frames[];
extern u8 troll_kind15_direction_frames[];
extern u8 troll_frame_set_8[];
extern u8 troll_frame_set_9[];
extern u8 troll_frame_set_10[];

/* Updates actor animation, facing, and actions from its dungeon state. */
/* Selects Troll's movement, attacks, spells, and turn processing using separate sprite tables for item
 * kinds 13 through 15. */
void update_actor_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state) {
    u16 path_info;
    u8 *next_row;
    s32 *current_row;
    s32 state_flags;
    s32 action_id;
    s32 heading;
    ActorRecord *player;
    s8 room_id;
    u16 *flags_page;
    u16 action_flags;
    s32 transition_mode;
    s32 action_mode;
    s32 anim_mode;
    s32 idle_mode;
    s32 effect_mode;
    s32 rest_mode;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        advance_actor_stored_path_2(actor, context, sprite, state);
        return;
    }
    if (state->mp == 0) {
        advance_actor_pending_action(actor, context, sprite, state);
        anim_mode = state->unk_48;
        switch (anim_mode) {
        case 0xD:
            if (*(s32 **)&sprite->frameTable == &troll_kind13_direction_frames) {
                return;
            }
            (sprite->frameTable) = &troll_frame_set_8;
            select_sprite_entry(sprite, ((u8 *)&troll_frame_set_8)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        case 0xE:
            if (*(s32 **)&sprite->frameTable == &troll_kind14_direction_frames) {
                return;
            }
            (sprite->frameTable) = &troll_frame_set_9;
            select_sprite_entry(sprite, ((u8 *)&troll_frame_set_9)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        case 0xF:
            if (*(s32 **)&sprite->frameTable == &troll_kind15_direction_frames) {
                return;
            }
            (sprite->frameTable) = &troll_frame_set_10;
            select_sprite_entry(sprite, ((u8 *)&troll_frame_set_10)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        }
        return;
    }
    if (state->flags1C & ACTOR_ASLEEP) {
        transition_mode = state->unk_48;
        switch (transition_mode) {
        case 0xD:
            if (*(s32 **)&sprite->frameTable == &troll_kind13_direction_frames) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = transition_mode;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &troll_frame_set_8) != 0) {
                return;
            }
            break;
        case 0xE:
            if (*(s32 **)&sprite->frameTable == &troll_kind14_direction_frames) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &troll_frame_set_9) != 0) {
                return;
            }
            break;
        case 0xF:
            if (*(s32 **)&sprite->frameTable == &troll_kind15_direction_frames) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &troll_frame_set_10) != 0) {
                return;
            }
            break;
        }
        flags_page = (u16 *)0x80080000;
    } else {
        flags_page = (u16 *)0x80080000;
    }
    if (!(flags_page[0x1A31] & 0x2000)) {
        if (state->flags1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, state);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            idle_mode = state->unk_48;
            switch (idle_mode) {
            case 0xD:
                if (*(s32 **)&sprite->frameTable != &troll_frame_set_1) {
                    (sprite->frameTable) = &troll_frame_set_1;
                    select_sprite_entry(sprite, ((u8 *)&troll_frame_set_1)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            case 0xE:
                if (*(s32 **)&sprite->frameTable != &troll_frame_set_2) {
                    (sprite->frameTable) = &troll_frame_set_2;
                    select_sprite_entry(sprite, ((u8 *)&troll_frame_set_2)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            case 0xF:
                if (*(s32 **)&sprite->frameTable != &troll_frame_set_3) {
                    (sprite->frameTable) = &troll_frame_set_3;
                    select_sprite_entry(sprite, ((u8 *)&troll_frame_set_3)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (state->hp_delta != 0) {
            effect_mode = state->unk_48;
            switch (effect_mode) {
            case 0xD:
                if (begin_ready_actor_directional_action(actor, context, sprite, &troll_frame_set_5) != 0) {
                    return;
                }
                break;
            case 0xE:
                if (begin_ready_actor_directional_action(actor, context, sprite, &troll_frame_set_6) != 0) {
                    return;
                }
                break;
            case 0xF:
                if (begin_ready_actor_directional_action(actor, context, sprite, &troll_frame_set_7) != 0) {
                    return;
                }
                break;
            }
        }
        if (state->flags1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, state);
            update_directional_action_display(actor, context, sprite, state);
            return;
        }
        if ((can_entity_gain_level(state) << 0x10) != 0) {
            process_selected_actor_record(actor, context, sprite, state);
        }
    }
    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;
    if (state->pending_turn_updates > 0) {
        if (state->flags1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(state);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            select_and_advance_actor_move(actor, context, sprite, state);
            return;
        }
        if (!(state->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(state, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((func_80173EAC(actor, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = state->action_flags | 0x4000;
            state->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                select_and_advance_actor_move(actor, context, sprite, state);
                return;
            }
        }
        action_id = state->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_id) {
        case 8:
        case 9:
            if ((check_and_prepare_actor_move(actor, context, sprite, state) << 0x10) != 0) {
                return;
            }
            prepare_actor_path_movement(actor, context, sprite, state);
            return;
        case 12:
            update_actor_status_and_mp(state);
            return;
        case 5:
        case 6:
        case 7:
        {
            heading = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_info);
        }
            player = primary_actor_record;
            state->facing = heading;
            if (player->action_id != 0x11) {
                update_actor_status_and_mp(state);
                return;
            }
        case 1:
        case 2:
        case 3:
            action_mode = state->unk_48;
            switch (action_mode) {
            case 0xD:
                begin_actor_spell_action(actor, context, sprite, &D_80175DF4, &update_actor_behavior);
                return;
            case 0xE:
                begin_actor_spell_action(actor, context, sprite, &D_80175DFC, &update_actor_behavior);
                return;
            case 0xF:
                begin_actor_spell_action(actor, context, sprite, &D_80175E04, &update_actor_behavior);
                return;
            }
            return;
        case 11:
        default:
            select_and_advance_actor_move(actor, context, sprite, state);
            return;
        }
    }
    state_flags = state->flags1C;
    if ((state_flags & 0x2000) || (room_id >= 0 && (dungeon_rooms[room_id].flags & 2)) || (state_flags & 0x430)) {
        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
    } else {
        if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
            state->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_info);
        }
        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
    }
    if (sprite->flags & 0x40) {
        return;
    }
    rest_mode = state->unk_48;
    switch (rest_mode) {
    case 0xD:
        current_row = sprite->frameTable;
        next_row = (u8 *)&troll_frame_set_1;
        break;
    case 0xE:
        current_row = sprite->frameTable;
        next_row = (u8 *)&troll_frame_set_2;
        break;
    case 0xF:
        current_row = sprite->frameTable;
        next_row = (u8 *)&troll_frame_set_3;
        break;
    default:
        return;
    }
    if (current_row == next_row) {
        return;
    }
    (sprite->frameTable) = next_row;
    select_sprite_entry(sprite, *(u8 *)((unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7)
        + (unsigned long)next_row), 0);
    return;
}
