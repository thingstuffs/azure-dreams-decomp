#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

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

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value();
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_8014F6B8(void *, void *, void *, void *);

extern u8 D_8014D514[];
extern u8 D_8014FE94[];
extern u8 D_8014FEBC[];
extern u8 D_8014FEC4[];
extern u8 D_8014FECC[];

/* Advances the actor state sequence and selects effects for its facing direction. */
void advance_facing_effect_sequence(ActorActionWork *action, void *context, SpriteFrameState *entity, EntityRec *actor)
{
    s32 direction;
    u8 *directionFrame;
    s32 next_state;
    u8 state;

    state = action->phase;
    switch (state) {
    case 0:
    {
        u8 *entryFrames;
        {
            DungeonGlobalStatus *dungeon_state;
            if ((entity->flags & 0xE000) == 0) {
                return;
            }

            entryFrames = D_8014FE94;

            entity->frameTable = entryFrames;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            direction &= 7;
            directionFrame = direction + entryFrames;
            select_sprite_entry(entity, *directionFrame, 0);
            dungeon_state = &g_dungeon_status;
            dungeon_state->activity_counts.parts.pending_action_count--;
            next_state = action->phase + 1;
            action->phase = next_state;
            return;
        }

    }

    case 1:
    {
        u8 *waitFrames;
        if (action->remainingAmount.signedValue != 0) {
            return;
        }
        waitFrames = D_8014FEBC;

        entity->frameTable = waitFrames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + waitFrames;
        select_sprite_entry(entity, *directionFrame, 0);
        action->phaseTicks = 0;
        next_state = action->phase + 1;
        action->phase = next_state;
        return;

    }

    case 2:
    {
        u8 *startFrames;
        if ((s16)action->phaseTicks++ < 2) {
            return;
        }
        startFrames = D_8014FEC4;

        entity->frameTable = startFrames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + startFrames;
        select_sprite_entry(entity, *directionFrame, 0);
        action->phaseTicks = 0;
        next_state = action->phase + 1;
        action->phase = next_state;
        return;

    }

    case 3:
    {
        u8 *finishFrames;
        if ((get_entity_effect_value(actor, 1) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                begin_ready_actor_directional_action(action, context, entity, 0)) {
                return;
            }

            if (actor->tileY == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                advance_actor_pending_action(action, context, entity, actor);
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                begin_pushed_actor_move(action, context, entity, actor);
                return;
            }

            {
                u32 adjustment_flag = 0x80000;
                if ((actor_flags & adjustment_flag) != 0) {
                    u16 remaining_amount;

                    begin_actor_move_to_target_facing(action, context, entity, actor);
                    remaining_amount = action->remainingAmount.value;
                    remaining_amount -= action->pendingAmount.value;
                    action->pendingAmount.value = 0;
                    action->adjustment = 0;
                    action->remainingAmount.value = remaining_amount;
                    func_8014F6B8(action, context, entity, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                EntityRec *owner = D_800814A8;

                if ((s16)check_entity_relation(actor,
                        (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *room_base = &D_80082E80;
                s8 room_id = *(s8 *)&entity->unk_26;

                if ((room_id == room_base->room_index && room_id >= 0) || (s16)get_tile_chebyshev_distance(room_base, entity) < 2) {
                    if ((generate_random_value() & 7) == 0) {
                        clear_slots_of_type(actor, 1);
                    }
                }
            }
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
        }

        finishFrames = D_8014FECC;

        entity->frameTable = finishFrames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + finishFrames;
        select_sprite_entry(entity, *directionFrame, 0);
        if ((entity->flags & 0x8000) != 0) {
            break;
        }
        action->phase++;
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            dungeon_state->activity_counts.parts.pending_action_count++;
        }
        return;

    }

    case 4:
    {
        u8 *restoreFrames;
        u32 phase_flag = 0x40000;
        u32 phase_flags;

        if ((entity->flags & 0xE000) == 0) {
            return;
        }

        restoreFrames = D_8014FE94;
        phase_flags = ((u32)actor->flags1C);

        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
        entity->frameTable = restoreFrames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + restoreFrames;
        select_sprite_entry(entity, *directionFrame, 0);
        action->phaseTicks = 0;
        next_state = action->phase + 1;
        action->phase = next_state;
        return;
    }

    case 5:
    {
        u8 *idleFrames;
        if ((s16)action->phaseTicks++ < 4) {
            return;
        }

        idleFrames = D_8014FE94;

        entity->frameTable = idleFrames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + idleFrames;
        select_sprite_entry(entity, *directionFrame, 0);
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            dungeon_state->activity_counts.parts.pending_action_count--;
        }
        break;

    }
    default:
        return;
    }

    action->handler = D_8014D514;
    return;
}
