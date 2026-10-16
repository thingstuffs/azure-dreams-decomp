#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

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

extern void func_80047784();
extern s32 dungeonCheckEntityRelation(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 dungeonCompareMonsterNeighborValues(s32, s32, s32, s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(ActorActionView *action, s32 unused, ActorSpriteView *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(ActorActionView *action, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8016B684(void *, void *, void *, void *);
extern void func_8016B8DC(void *, void *, void *, void *);
extern s32 func_8016C088(void *, void *, void *, void *);
extern void func_8016C24C(void *, void *, void *, void *);
extern s32 func_8016C364(void *, void *, void *, s32);
extern void func_8016E060(void *, void *, void *, void *);
extern void func_8016E234(void *, void *, void *, void *);
extern void dungeonSpawnOwnedMotionObject(void *, void *, void *, void *);

extern u8 D_800DCF5B;
extern u8 D_8016EF00[];
extern u8 D_8016EF08[];
extern u8 D_8016EF38;
extern u8 D_8016EF40;
extern u8 D_8016EF48;

/* Updates dungeon action behavior, facing, and animation from its current state. */
void dungeonUpdateActionBehaviorFacingAndAnimation(ActorActionView *action, void *context, ActorSpriteView *sprite, EntityRec *entity)
{
    u8 *anim_table;
    s32 direction_flags;
    s8 room_id;
    u16 action_state;
    u16 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        action->behavior = 0xE;
        func_8016B684(action, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        dungeonAdvanceActorPendingAction(action, context, sprite, entity);
        if (sprite->frameTable != &D_8016EF48) {
            u8 *next_anim_table = &D_8016EF40;

            (sprite->frameTable) = next_anim_table;
            func_80047784(sprite,
                next_anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (sprite->frameTable == &D_8016EF48) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextBehavior = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (dungeonResetActorActionState(action, context, sprite, &D_8016EF40) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(action, context, sprite, entity);
            return;
        }

        if (action->behavior != 0xE) {
            u8 actor_state = 0xE;

            anim_table = D_8016EF00;
            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            action->behavior = actor_state;
        }

        action->flags &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(action, context, sprite, D_8016EF08) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            func_800AA888(action, context, sprite, entity);
            func_8016E060(action, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            dungeonProcessSelectedActorRecord(action, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(sprite->tile.bytes.x, sprite->tile.bytes.y);
    sprite->room.raw = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (sprite->tile.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8016B8DC(action, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((dungeonCheckEntityRelation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016C364(action, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->unk_46 | 0x4000;
            entity->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_8016B8DC(action, context, sprite, entity);
                return;
            }
        }

        action_state = entity->unk_46 & 0x3FFF;
        switch (action_state) {
        case 8:
            if ((func_8016C088(action, context, sprite, entity) << 16) == 0) {
                func_8016C24C(action, context, sprite, entity);
            }
            return;

        case 10:
            dungeonSpawnOwnedMotionObject(action, context, sprite, entity);
            return;

        case 9:
            if (D_800DCF5B != 0) {
                break;
            }
            func_8016E234(action, context, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 facing_angle;

            facing_angle = dungeonGetRoundedFacingAndRoundingFlag(
                sprite->tile.bytes.x, sprite->tile.bytes.y,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_flags);
            player = D_800814A8;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(action, context, sprite, &D_8016EF38, dungeonUpdateActionBehaviorFacingAndAnimation);
                return;
            }
        }

        case 12:
            func_800A9A0C(entity);
            return;

        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(action, context, sprite, &D_8016EF38, dungeonUpdateActionBehaviorFacingAndAnimation);
            return;

        case 11:
        case 4:
        default:
            break;
        }
        func_8016B8DC(action, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((dungeonCompareMonsterNeighborValues(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
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
    anim_table = D_8016EF00;
    if (sprite->frameTable == anim_table) {
        return;
    }

    (sprite->frameTable) = anim_table;
    func_80047784(sprite,
        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
