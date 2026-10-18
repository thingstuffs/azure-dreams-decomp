#include "common.h"
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

/* Resident bindings traced in this bank; shared record layouts retained. */
extern GameWork D_80084818;
extern DungeonGlobalStatus D_80085990;
extern TileObject D_80081490;
extern struct EntityRec * D_800803DC;

extern s32 func_800424C4(void *, s32);
extern void func_8004272C(void *, s32);
extern void func_80047320(void *, u8, s32);
extern s32 func_80098F70(void *, void *);
extern s32 func_8009EB30(void *, void *);
extern s32 func_800A1904(void *);
extern s32 func_800A59E8();
extern void update_fading_effect_motion(void *);
extern void func_800A86C4(void *);
extern void func_800A8F10(void *, void *, void *, void *);
extern s32 func_800A936C(void *, void *, void *, s32);
extern void func_800A9454(void *, void *, void *, void *);
extern void func_800A9540(void *, void *, void *, void *);
extern void func_801606B8(void *, void *, void *, void *);

extern u8 D_8015E514[];
extern u8 D_80160E94[];
extern u8 D_80160EBC[];
extern u8 D_80160EC4[];
extern u8 D_80160ECC[];

/* Advances the actor state sequence and selects effects for its facing direction. */
void advance_actor_facing_effect_state(ActorActionWork *action, void *context, Rec_D_80082E80 *entity, EntityRec *actor)
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
            if ((entity->unk_14.at00_u16.v & 0xE000) == 0) {
                return;
            }

            entryFrames = D_80160E94;

            entity->unk_2C.as_pv = entryFrames;
            direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
            direction &= 7;
            directionFrame = direction + entryFrames;
            func_80047320(entity, *directionFrame, 0);
            dungeon_state = &D_80085990;
            dungeon_state->unk_0A--;
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
        waitFrames = D_80160EBC;

        entity->unk_2C.as_pv = waitFrames;
        direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + waitFrames;
        func_80047320(entity, *directionFrame, 0);
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
        startFrames = D_80160EC4;

        entity->unk_2C.as_pv = startFrames;
        direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + startFrames;
        func_80047320(entity, *directionFrame, 0);
        action->phaseTicks = 0;
        next_state = action->phase + 1;
        action->phase = next_state;
        return;

    }

    case 3:
    {
        u8 *finishFrames;
        if ((func_800424C4(actor, 1) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &D_80085990;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                func_800A936C(action, context, entity, 0)) {
                return;
            }

            if (actor->tileY == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                func_800A9454(action, context, entity, actor);
                return;
            }

            if ((s16)func_800A1904(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                func_800A8F10(action, context, entity, actor);
                return;
            }

            {
                u32 adjustment_flag = 0x80000;
                if ((actor_flags & adjustment_flag) != 0) {
                    u16 remaining_amount;

                    func_800A9540(action, context, entity, actor);
                    remaining_amount = action->remainingAmount.value;
                    remaining_amount -= action->pendingAmount.value;
                    action->pendingAmount.value = 0;
                    action->adjustment = 0;
                    action->remainingAmount.value = remaining_amount;
                    func_801606B8(action, context, entity, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)func_800A1904(actor) != 0) {
                EntityRec *owner = D_800803DC;

                if ((s16)func_80098F70(actor,
                        (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A86C4(actor);
            update_fading_effect_motion(actor);
            if ((func_800424C4(actor, 1) << 16) != 0) {
                TileObject *room_base = &D_80081490;
                s8 room_id = entity->unk_26.as_s8;

                if ((room_id == room_base->unk_026 && room_id >= 0) || (s16)func_8009EB30(room_base, entity) < 2) {
                    if ((func_800A59E8() & 7) == 0) {
                        func_8004272C(actor, 1);
                    }
                }
            }
            if ((func_800424C4(actor, 1) << 16) != 0) {
                return;
            }
        }

        finishFrames = D_80160ECC;

        entity->unk_2C.as_pv = finishFrames;
        direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + finishFrames;
        func_80047320(entity, *directionFrame, 0);
        if ((entity->unk_14.at00_u16.v & 0x8000) != 0) {
            break;
        }
        action->phase++;
        {
            DungeonGlobalStatus *dungeon_state = &D_80085990;
            dungeon_state->unk_0A++;
        }
        return;

    }

    case 4:
    {
        u8 *restoreFrames;
        u32 phase_flag = 0x40000;
        u32 phase_flags;

        if ((entity->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        restoreFrames = D_80160E94;
        phase_flags = ((u32)actor->flags1C);

        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
        entity->unk_2C.as_pv = restoreFrames;
        direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + restoreFrames;
        func_80047320(entity, *directionFrame, 0);
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

        idleFrames = D_80160E94;

        entity->unk_2C.as_pv = idleFrames;
        direction = (D_80084818.view.viewAngle + actor->facing + 0x100) >> 9;
        direction &= 7;
        directionFrame = direction + idleFrames;
        func_80047320(entity, *directionFrame, 0);
        {
            DungeonGlobalStatus *dungeon_state = &D_80085990;
            dungeon_state->unk_0A--;
        }
        break;

    }
    default:
        return;
    }

    action->handler = D_8015E514;
    return;
}
