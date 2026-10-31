#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/state.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_8016B438(void *, void *, void *, void *);
extern void func_8016B67C(void *, void *, void *, void *);
extern s32 func_8016BE28(void *, void *, void *, void *);
extern void func_8016C08C(void *, void *, void *, void *);
extern s32 func_8016C230(void *, void *, void *, s32);
extern void func_8016DA84(void *, void *, void *, void *);

extern u8 dungeon_action_resume_address;
extern u8 killer_slot_f_default_frames[];
extern u8 D_8016E040[];
extern u8 D_8016E070[];
extern u8 bank_actor_default_frames[];
extern u8 bank_actor_action_frames[];

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 action;
    u8 phase;
} ActionState;

typedef struct ActorSprite {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    u8 room;
    u8 pad_27[0x5];
    void * directionFrames;
} ActorSprite;

/* Updates the entity action, facing direction, and animation from dungeon state. */
void update_dungeon_entity_action_and_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        body->action_id.u = 0xE;
        func_8016B438(body, position, sprite, actor);
        return;
    }

    if (actor->mp_value.parts.whole == 0) {
        advance_actor_pending_action(body, position, sprite, actor);
        if (sprite->frameTable != bank_actor_action_frames) {
            sprite->frameTable = bank_actor_default_frames;
            select_sprite_entry(sprite,
                bank_actor_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)actor->flags1C) & 0x200) {
        if (sprite->frameTable == bank_actor_action_frames) {
            body->action_id.u = 0xD;
            body->action_phase.u = 1;
            body->unk_8C.word = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(body, position, sprite, bank_actor_default_frames)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & 0x100) {
            begin_pushed_actor_move(body, position, sprite, actor);
            return;
        }

        if (body->action_id.u != 0xE) {
            u8 next_state = 0xE;

            anim_table = killer_slot_f_default_frames;
            if (sprite->frameTable != anim_table) {
                sprite->frameTable = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            body->action_id.u = next_state;
        }

        body->action_state_flags &= 0xFFF3;
        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(body, position, sprite, D_8016E040)) {
                    return;
            }
        }

        if (((u32)actor->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(body, position, sprite, actor);
            func_8016DA84(body, position, sprite, actor);
            return;
        }

        if ((s16)can_entity_gain_level(actor) != 0) {
            process_selected_actor_record(body, position, sprite, actor);
        }
    }

    tile_record = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_record;

    if (actor->pending_turn_updates > 0) {
        if (((u32)actor->flags1C) & 0x20) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_8016B67C(body, position, sprite, actor);
            return;
        }
        if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016C230(body, position, sprite, 0) == 0) {
                    return;
            }
            actor->action_flags |= 0x4000;
            if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
                func_8016B67C(body, position, sprite, actor);
                return;
            }
        }

        switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 9:
            body->action_state_flags |= 0x8000;
        /* fall through */
        case 8:
            if (((u32)actor->flags1C) & 0x2000) {
                if ((actor->action_flags & ACTOR_ACTION_CODE_MASK) == 8) {
                    body->action_state_flags &= 0x7FFF;
                }
            }
            if ((s16)func_8016BE28(body, position, sprite, actor) == 0) {
                func_8016C08C(body, position, sprite, actor);
                    return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                global_actor = primary_actor_record;
                actor->facing = direction;
                if (global_actor->action_id.u == 0x11) {
                    begin_actor_spell_action(body, position, sprite, D_8016E070, &dungeon_action_resume_address);
                    return;
                }
            }
        /* fall through */
        case 12:
            update_actor_status_and_mp(actor);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(body, position, sprite, D_8016E070, &dungeon_action_resume_address);
            return;
        default:
            func_8016B67C(body, position, sprite, actor);
            return;
        }
    } else if (!(((u32)actor->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & 0x430)) {

                if ((s16)test_neighbor_position_relation(sprite->tile_x,
                        sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
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
    anim_table = killer_slot_f_default_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    sprite->frameTable = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
}
