#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* Sprite state passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

extern void func_80047784();
extern s32 dungeonCheckEntityRelation(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 dungeonCompareMonsterNeighborValues(u8, u8, u8, u8);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(void *actor, s32 unused, ActorSpriteView *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8017224C(void *, void *, void *, void *);
extern void func_80172490(void *, void *, void *, void *);
extern s32 func_80172C44(void *, void *, void *, void *);
extern void func_80172E08(void *, void *, void *, void *);
extern s32 func_80172F20(void *, void *, void *, s32);
extern void func_80174650(void *, void *, void *, void *);
extern void dungeonResetActorActionStateAfterCompletion(void *, void *, void *, void *);

extern u8 D_80174EB8[];
extern u8 D_80174EC0[];
extern u8 D_80174EF0[];
extern u8 D_80174EF8[];
extern u8 D_80174F00[];

/* Updates an actor's dungeon behavior, facing, and animation. */
void dungeonUpdateEffectActorBehavior(ActorActionView *action, void *context, ActorSpriteView *sprite, EntityRec *entity)
{
    u32 initial_flags = dungeonStatus.flags;
    s16 distance;
    s32 status_flags;
    s8 room_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    EntityRec *player;

    if (initial_flags & 0x1000) {
        action->behavior = 14;
        func_8017224C(action, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        dungeonAdvanceActorPendingAction(action, context, sprite, entity);
        if (sprite->frameTable == D_80174F00) {
            return;
        }
        {
            u8 *early_anim_table = D_80174EF8;
            (sprite->frameTable) = early_anim_table;
            func_80047784(
                sprite,
                early_anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (entity->flags1C & 0x200) {
        if (sprite->frameTable == D_80174F00) {
            action->behavior = 13;
            action->phase = 1;
            action->nextBehavior = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(action, context, sprite, D_80174EF8) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (entity->flags1C & 0x100) {
            dungeonBeginPushedActorMove(action, context, sprite, entity);
            return;
        }

        {
            u8 current_state = action->behavior;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_80174EB8;
                if (sprite->frameTable != anim_table) {
                    (sprite->frameTable) = anim_table;
                    func_80047784(
                        sprite,
                        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                }
                action->behavior = next_state;
            }
        }

        action->flags &= 0xFFF3;

        if (entity->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(action, context, sprite, D_80174EC0) != 0) {
                    return;
            }
        }

        if (entity->flags1C & 0x80000) {
            func_800AA888(action, context, sprite, entity);
            func_80174650(action, context, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            dungeonProcessSelectedActorRecord(action, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(sprite->tile.bytes.x, sprite->tile.bytes.y);
    sprite->room.signedValue = room_id;

    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (sprite->tile.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_80172490(action, context, sprite, entity);
            return;
        }
        action_flags = entity->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(
                        entity, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172F20(action, context, sprite, 0) == 0) {
                    return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_80172490(action, context, sprite, entity);
                return;
            }
        }

        switch (entity->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80172C44(action, context, sprite, entity) != 0) {
                    return;
            }
            func_80172E08(action, context, sprite, entity);
            return;
        case 9:
            dungeonResetActorActionStateAfterCompletion(action, context, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            facing = dungeonGetRoundedFacingAndRoundingFlag(
                sprite->tile.bytes.x, sprite->tile.bytes.y,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            player = D_800814A8;
            entity->facing = facing;
            if (player->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(action, context, sprite, D_80174EF0, dungeonUpdateEffectActorBehavior);
                    return;
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(entity);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(action, context, sprite, D_80174EF0, dungeonUpdateEffectActorBehavior);
            return;
        default:
            func_80172490(action, context, sprite, entity);
            return;
        }
    }

    status_flags = entity->flags1C;
    if (!(status_flags & 0x2000)) {
        if ((room_id < 0) ||
            !(D_800E2970[room_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)dungeonCompareMonsterNeighborValues(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    entity->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY, &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = D_80174EB8;
    if (sprite->frameTable == anim_table) {
        return;
    }

    (sprite->frameTable) = anim_table;
    func_80047784(
        sprite,
        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
