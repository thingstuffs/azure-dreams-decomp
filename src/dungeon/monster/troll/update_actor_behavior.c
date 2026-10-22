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


typedef struct S_801724BC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    s32 * unk_2C;
} S_801724BC_2;   /* arg2 in update_actor_behavior */


/* cfail-repair: tf7-phase1-cache-v3 */
void select_sprite_entry();         /* extern */
s32 check_entity_relation();                     /* extern */
s8 find_active_rect_containing_point();                           /* extern */
s32 test_neighbor_position_relation();                  /* extern */
s32 get_rounded_facing_and_rounding_flag();       /* extern */
s32 can_entity_gain_level();                          /* extern */
void update_actor_status_and_mp();                      /* extern */
void begin_pushed_actor_move(); /* extern */
s32 begin_ready_actor_directional_action(); /* extern */
s32 advance_actor_pending_action(); /* extern */
void begin_actor_move_to_target_facing(); /* extern */
s32 reset_actor_action_state(); /* extern */
s32 process_selected_actor_record(); /* extern */
void begin_actor_spell_action(); /* extern */
void advance_actor_stored_path_2(void *movement, s32 actor_index, void *actor, void *path_state);                            /* extern */
void select_and_advance_actor_move(); /* extern */
s32 check_and_prepare_actor_move(); /* extern */
void prepare_actor_path_movement(); /* extern */
s32 func_80173EAC(); /* extern */
void update_directional_action_display(); /* extern */
void update_actor_behavior(void *actor, s32 context, void *sprite, ActorRecord *state);
extern M2C_UNK D_80175DF4;
extern M2C_UNK D_80175DFC;
extern M2C_UNK D_80175E04;
extern M2C_UNK D_80175E24;
extern M2C_UNK D_80175E2C;
extern M2C_UNK D_80175E34;
extern M2C_UNK D_80175E3C;
extern M2C_UNK D_80175E44;
extern M2C_UNK D_80175E4C;
extern M2C_UNK D_80175E54;
extern M2C_UNK D_80175E5C;
extern M2C_UNK D_80175E64;
extern M2C_UNK D_80175E84;
extern M2C_UNK D_80175E8C;
extern M2C_UNK D_80175E94;

/* Updates actor animation, facing, and actions from its dungeon state. */
/* Selects Troll's movement, attacks, spells, and turn processing using separate sprite tables for item
 * kinds 13 through 15. */
void update_actor_behavior(void *actor, s32 context, void *sprite, ActorRecord *state) {
    s32 path_info;
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
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E54) {
                return;
            }
            (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E84;
            select_sprite_entry(sprite, ((u8 *)&D_80175E84)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        case 0xE:
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E5C) {
                return;
            }
            (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E8C;
            select_sprite_entry(sprite, ((u8 *)&D_80175E8C)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        case 0xF:
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E64) {
                return;
            }
            (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E94;
            select_sprite_entry(sprite, ((u8 *)&D_80175E94)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7], 0);
            return;
        }
        return;
    }
    if (state->flags1C & 0x200) {
        transition_mode = state->unk_48;
        switch (transition_mode) {
        case 0xD:
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E54) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = transition_mode;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &D_80175E84) != 0) {
                return;
            }
            break;
        case 0xE:
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E5C) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &D_80175E8C) != 0) {
                return;
            }
            break;
        case 0xF:
            if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E64) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                state->flags1C = (s32) (state->flags1C & 0xFFFBFFFF);
                return;
            }
            if (reset_actor_action_state(actor, context, sprite, &D_80175E94) != 0) {
                return;
            }
            break;
        }
        flags_page = (u16 *)0x80080000;
    } else {
        flags_page = (u16 *)0x80080000;
    }
    if (!(flags_page[0x1A31] & 0x2000)) {
        if (state->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, state);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            idle_mode = state->unk_48;
            switch (idle_mode) {
            case 0xD:
                if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E24) {
                    (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E24;
                    select_sprite_entry(sprite, ((u8 *)&D_80175E24)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            case 0xE:
                if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E2C) {
                    (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E2C;
                    select_sprite_entry(sprite, ((u8 *)&D_80175E2C)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            case 0xF:
                if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E34) {
                    (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80175E34;
                    select_sprite_entry(sprite, ((u8 *)&D_80175E34)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                        >> 9) & 7], 0);
                }
                break;
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (state->unk_64 != 0) {
            effect_mode = state->unk_48;
            switch (effect_mode) {
            case 0xD:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80175E3C) != 0) {
                    return;
                }
                break;
            case 0xE:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80175E44) != 0) {
                    return;
                }
                break;
            case 0xF:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80175E4C) != 0) {
                    return;
                }
                break;
            }
        }
        if (state->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, state);
            update_directional_action_display(actor, context, sprite, state);
            return;
        }
        if ((can_entity_gain_level(state) << 0x10) != 0) {
            process_selected_actor_record(actor, context, sprite, state);
        }
    }
    room_id = find_active_rect_containing_point(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v);
    ((S_801724BC_2 *)sprite)->unk_26 = room_id;
    if (state->pending_turn_updates > 0) {
        if (state->flags1C & 0x20) {
            update_actor_status_and_mp(state);
            return;
        }
        if (((S_801724BC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
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
            heading = get_rounded_facing_and_rounding_flag(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_info);
        }
            player = primary_actor_record;
            state->facing = heading;
            if (player->unk_9A != 0x11) {
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
        if ((test_neighbor_position_relation(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
            state->facing = get_rounded_facing_and_rounding_flag(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_info);
        }
        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
    }
    if (((S_801724BC_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    rest_mode = state->unk_48;
    switch (rest_mode) {
    case 0xD:
        current_row = ((S_801724BC_2 *)sprite)->unk_2C;
        next_row = (u8 *)&D_80175E24;
        break;
    case 0xE:
        current_row = ((S_801724BC_2 *)sprite)->unk_2C;
        next_row = (u8 *)&D_80175E2C;
        break;
    case 0xF:
        current_row = ((S_801724BC_2 *)sprite)->unk_2C;
        next_row = (u8 *)&D_80175E34;
        break;
    default:
        return;
    }
    if (current_row == next_row) {
        return;
    }
    (*(s32 **)((u8 *)sprite + 0x2C)) = next_row;
    select_sprite_entry(sprite, *(u8 *)((unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7)
        + (unsigned long)next_row), 0);
    return;
}
