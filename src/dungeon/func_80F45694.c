#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

extern void func_80047784(void *, u8, s32);
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
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8015F3F8(void *, void *, void *, void *);
extern void func_8015F63C(void *, void *, void *, void *);
extern s32 func_8015FDFC(void *, void *, void *, void *);
extern void func_8015FFC0(void *, void *, void *, void *);
extern s32 func_801601F8(void *, void *, void *, s32);
extern void func_80162278(void *, void *, void *, void *);
extern void func_801600D8(void *, void *, void *, void *);

extern u8 D_80162A7C[];
extern u8 D_80162A84[];
extern u8 D_80162AC4[];
extern u8 D_80162ACC[];
extern u8 D_80162AD4[];

void dungeonUpdateActorMovementVariant(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *entity)
{
    u32 initial_flags = dungeonStatus.flags;
    s16 facing_aux;
    s32 status_flags;
    s8 tile_id;
    s16 facing_angle;
    u16 action_flags;
    u8 *anim_table;
    EntityRec *player;

    if (initial_flags & 0x1000) {
        action->behavior = 14;
        func_8015F3F8(action, motion, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        dungeonAdvanceActorPendingAction(action, motion, sprite, entity);
        if (sprite->directionFrames == D_80162AD4) {
            return;
        }
        {
            u8 *early_anim_table = D_80162ACC;
            sprite->directionFrames = early_anim_table;
            func_80047784(
                sprite,
                early_anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (entity->flags1C & 0x200) {
        if (sprite->directionFrames == D_80162AD4) {
            action->behavior = 13;
            action->phase = 1;
            action->nextAction.code = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(action, motion, sprite, D_80162ACC) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (entity->flags1C & 0x100) {
            dungeonBeginPushedActorMove(action, motion, sprite, entity);
            return;
        }

        {
            u8 current_state = action->behavior;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_80162A7C;
                if (sprite->directionFrames != anim_table) {
                    sprite->directionFrames = anim_table;
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
            if (dungeonBeginReadyActorDirectionalAction(action, motion, sprite, D_80162A84) != 0) {
                return;
            }
        }

        if (entity->flags1C & 0x80000) {
            func_800AA888(action, motion, sprite, entity);
            func_80162278(action, motion, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            dungeonProcessSelectedActorRecord(action, motion, sprite, entity);
        }
    }

    tile_id = func_8009FB34(sprite->position.tile.x, sprite->position.tile.y);
    sprite->tileIndex.signedIndex = tile_id;

    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (sprite->position.packed == ((TilePairView *)&D_80082E80.tileX)->packed) {
            func_8015F63C(action, motion, sprite, entity);
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
            if ((s16)func_801601F8(action, motion, sprite, 0) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8015F63C(action, motion, sprite, entity);
            return;
            }
        }

        switch (entity->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_8015FDFC(action, motion, sprite, entity) != 0) {
                return;
            }
            func_8015FFC0(action, motion, sprite, entity);
            return;
        case 9:
            func_801600D8(action, motion, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            facing_angle = dungeonGetRoundedFacingAndRoundingFlag(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
            player = D_800814A8;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(action, motion, sprite, D_80162AC4, dungeonUpdateActorMovementVariant);
                return;
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(entity);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(action, motion, sprite, D_80162AC4, dungeonUpdateActorMovementVariant);
            return;
        default:
            func_8015F63C(action, motion, sprite, entity);
            return;
        }
    }

    status_flags = entity->flags1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(D_800E2970[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)dungeonCompareMonsterNeighborValues(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    entity->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
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
    anim_table = D_80162A7C;
    if (sprite->directionFrames == anim_table) {
        return;
    }

    sprite->directionFrames = anim_table;
    func_80047784(
        sprite,
        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
