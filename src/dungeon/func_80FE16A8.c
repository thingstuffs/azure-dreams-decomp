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
void update_dungeon_entity_action_and_facing(ActionState *actor, void *context, SpriteFrameState *sprite, ActorRecord *entity)
{
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        actor->action = 0xE;
        func_8016B438(actor, context, sprite, entity);
        return;
    }

    if (entity->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable != bank_actor_action_frames) {
            sprite->frameTable = bank_actor_default_frames;
            select_sprite_entry(sprite,
                bank_actor_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (sprite->frameTable == bank_actor_action_frames) {
            actor->action = 0xD;
            actor->phase = 1;
            actor->handler = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, bank_actor_default_frames)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (actor->action != 0xE) {
            u8 next_state = 0xE;

            anim_table = killer_slot_f_default_frames;
            if (sprite->frameTable != anim_table) {
                sprite->frameTable = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->action = next_state;
        }

        actor->flags &= 0xFFF3;
        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8016E040)) {
                    return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_8016DA84(actor, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    tile_record = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_record;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_8016B67C(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016C230(actor, context, sprite, 0) == 0) {
                    return;
            }
            entity->action_flags |= 0x4000;
            if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
                func_8016B67C(actor, context, sprite, entity);
                return;
            }
        }

        switch (entity->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 9:
            actor->flags |= 0x8000;
        /* fall through */
        case 8:
            if (((u32)entity->flags1C) & 0x2000) {
                if ((entity->action_flags & ACTOR_ACTION_CODE_MASK) == 8) {
                    actor->flags &= 0x7FFF;
                }
            }
            if ((s16)func_8016BE28(actor, context, sprite, entity) == 0) {
                func_8016C08C(actor, context, sprite, entity);
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
                entity->facing = direction;
                if (global_actor->action_id.u == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_8016E070, &dungeon_action_resume_address);
                    return;
                }
            }
        /* fall through */
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, context, sprite, D_8016E070, &dungeon_action_resume_address);
            return;
        default:
            func_8016B67C(actor, context, sprite, entity);
            return;
        }
    } else if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((s16)test_neighbor_position_relation(sprite->tile_x,
                        sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
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
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
