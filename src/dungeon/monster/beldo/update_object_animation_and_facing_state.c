#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s32 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8016B9C0(void *, s32, void *, void *);
extern void func_8016BBE0(void *, void *, void *, void *);
extern s32 func_8016C330(void *, void *, void *, s32);
extern void func_8016D6B8(void *, void *, void *, void *);
extern void func_8016DD6C(void *, void *, void *);

extern u8 D_8016B514;
extern u8 D_8016DE8C[8];
extern u8 D_8016DE94[];
extern u8 D_8016DEC4[];
extern u8 D_8016DEE4[];

typedef struct ActorActionWork {
    u8 pad_00[0x8C];
    void *handler;
    u8 pad_90[2];
    union { s16 signedValue; u16 value; } remainingAmount;
    u8 pad_94[2];
    u16 phaseTicks;
    u16 actionFlags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    u16 adjustment;
    u8 pad_A0[2];
    union { s16 signedValue; u16 value; } pendingAmount;
} ActorActionWork;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 animationKind;
    u8 animationEnabled;
    u8 pad_06[0xE];
    u16 animationFlags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    union { s8 signedValue; u8 value; } roomId;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Updates object animation, dispatches its action, and adjusts its facing. */
void update_object_animation_and_facing_state(ActorActionWork *action, void *context, ActorSpriteView *sprite, ActorRecord *actor)
{
    u32 entry_status = g_dungeon_status.flags;
    s32 state_flags;
    s32 roomOrDirection;
    s32 action_kind;
    s32 jump_index;
    s32 entry_index;
    DungeonRoom *roomTable;
    DungeonRoom *roomEntry;
    s16 distance;
    void *callback_state;

    if (entry_status & 0x1000) {
        action->behavior = 14;
        func_8016B9C0(action, (s32)context, sprite, actor);
        return;
    }

    if (actor->flags1C & 0x200) {
        if (sprite->directionFrames == D_8016DEC4) {
            action->behavior = 13;
            action->phase = 1;
            action->handler = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, context, sprite, D_8016DE94) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (actor->flags1C & 0x100) {
            begin_pushed_actor_move(action, context, sprite, actor);
            return;
        }

        if (action->behavior != 14) {
            action->behavior = 14;
        }
        if (sprite->directionFrames != D_8016DE8C) {
            sprite->directionFrames = D_8016DE8C;
            select_sprite_entry(
                sprite,
                D_8016DE8C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->animationEnabled = 1;
            action->pendingAmount.signedValue = 0;
            action->adjustment = 0;
        }

        actor->flags1C |= 0x40000;
        action->actionFlags &= 0xFFF7;

        if (actor->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, D_8016DEE4) != 0) {
                return;
            }
        }

        if (actor->flags1C & 0x80000) {
            u16 previous_amount;
            u16 pending_amount;

            begin_actor_move_to_target_facing(action, context, sprite, actor);
            previous_amount = action->remainingAmount.value;
            pending_amount = action->pendingAmount.value;
            action->pendingAmount.signedValue = 0;
            action->adjustment = 0;
            action->remainingAmount.value = previous_amount - pending_amount;
            func_8016D6B8(action, context, sprite, actor);
            return;
        }

        if ((s16)can_entity_gain_level(actor) != 0) {
            process_selected_actor_record(action, context, sprite, actor);
        }
    }

    roomOrDirection = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->roomId.value = roomOrDirection;

    if (actor->pending_turn_updates > 0) {
        if (actor->flags1C & 0x20) {
            update_actor_status_and_mp(actor);
            return;
        }

        if (sprite->position.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8016BBE0(action, context, sprite, actor);
            return;
        }

        if ((actor->action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        actor, (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            if (system_update_flags & 8) {
                u8 callback_flags;

                func_8016DD6C(action, context, sprite);
                callback_flags = actor->movement_queue_state;
                callback_state = actor;
                callback_flags &= 0x7F;
                actor->movement_queue_state = callback_flags;
                update_actor_status_and_mp(callback_state);
                actor->action_flags &= 0x7FFF;
                return;
            }

            if ((s16)func_8016C330(action, context, sprite, 0) == 0) {
                return;
            }
            actor->action_flags |= 0x4000;
            if ((actor->action_flags & 0x8000) == 0) {
                func_8016BBE0(action, context, sprite, actor);
                return;
            }
        }

        action_kind = actor->action_flags & 0x3FFF;
        jump_index = action_kind - 1;
        switch (jump_index) {
        case 11:
            update_actor_status_and_mp(actor);
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            callback_state = actor;
            action->handler = &D_8016B514;
            update_actor_status_and_mp(callback_state);
            actor->action_flags &= 0x7FFF;
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(action, context, sprite, 0, &D_8016B514);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_8016BBE0(action, context, sprite, actor);
            return;
        }
    }

    state_flags = actor->flags1C;
    if ((state_flags & 0x2000) == 0) {
        entry_index = (s8)roomOrDirection;
        if (entry_index >= 0) {
            roomTable = dungeon_rooms;
            roomEntry = &roomTable[entry_index];
            if (roomEntry->flags & 2) {
                return;
            }
        }
        if ((state_flags & 0x430) == 0) {
            if ((s16)test_neighbor_position_relation(
                    sprite->position.tile.x, sprite->position.tile.y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                roomOrDirection = get_rounded_facing_and_rounding_flag(
                    sprite->position.tile.x, sprite->position.tile.y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                actor->facing = roomOrDirection;
            }
        }
    }
}
