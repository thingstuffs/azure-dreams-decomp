#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 dungeonCheckEntityRelation(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 dungeonCompareMonsterNeighborValues(s32, s32, s32, s32);
extern s32 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015F510(void *, void *, void *, void *);
extern void func_8015F768(u8 *move_work, void *entry_context, u8 *position, u8 *actor);
extern s32 func_8015FF24(void *, void *, void *, void *);
extern void func_80160110(void *, void *, void *, void *);
extern s32 func_80160228(void *, void *, void *, s32);
extern void func_80161900(void *, void *, void *, void *);
extern void func_80161AD4(void *, void *, void *, void *);

extern s32 D_8015EF68;
extern u8 D_80161FB8[];
extern u8 D_80161FC0[];
extern u8 D_80161FF0[];
extern u8 D_80161FF8[];
extern u8 D_80162000[];

typedef struct CreatureState {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[0x5];
    u8 tileY;
    u8 pad_26[0x4];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x1C];
    s16 reaction;
    u8 pad_66[0x7];
    s8 actionsLeft;
} CreatureState;

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

/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void updateDungeonActorBehaviorAndAnimation(void *actor, void *context, ActorSprite *sprite, CreatureState *entity)
{
    u8 *anim_table;
    s32 tile_id;
    s32 direction_aux;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_8015F510(actor, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        u8 *inactive_anims;

        dungeonAdvanceActorPendingAction(actor, context, sprite, entity);
        if (sprite->directionFrames != D_80162000) {
            inactive_anims = D_80161FF8;
            sprite->directionFrames = inactive_anims;
            func_80047784(sprite,
                inactive_anims[((gameWork.view.viewAngle + entity->facing + 0x100)
                    >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
        func_80042B68(entity, 0x1A);
        return;
    }

    if (entity->flags & 0x200) {
        if (sprite->directionFrames == D_80162000) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(actor, context, sprite, D_80161FF8)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (entity->flags & 0x100) {
            dungeonBeginPushedActorMove(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80161FB8;
            if (sprite->directionFrames != anim_table) {
                sprite->directionFrames = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + entity->facing + 0x100)
                        >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (entity->reaction != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor, context, sprite, D_80161FC0)) {
                    return;
            }
        }

        if (entity->flags & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_80161900(actor, context, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            dungeonProcessSelectedActorRecord(actor, context, sprite, entity);
        }
    }

    tile_id = func_8009FB34(sprite->position.tile.x,
        sprite->position.tile.y);
    sprite->room = tile_id;

    if (entity->actionsLeft > 0) {
        if (entity->flags & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8015F768(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80160228(actor, context, sprite, 0) == 0) {
                    return;
            }
            entity->action |= 0x4000;
            if (!(entity->action & 0x8000)) {
                func_8015F768(actor, context, sprite, entity);
                return;
            }
        }

        switch (entity->action & 0x3FFF) {
        case 8:
            if ((s16)func_8015FF24(actor, context, sprite, entity) == 0) {
                func_80160110(actor, context, sprite, entity);
                    return;
            }
            return;
        case 9:
            func_80161AD4(actor, context, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s32 direction;

                direction = dungeonGetRoundedFacingAndRoundingFlag(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_aux);
                player = D_800814A8;
                entity->facing = direction;
                if (player->unk_9A == 0x11) {
                    dungeonBeginActorSpellAction(actor, context, sprite, D_80161FF0, &D_8015EF68);
                    return;
                }
            }
        /* fall through */
        case 12:
            func_800A9A0C(entity);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(actor, context, sprite, D_80161FF0, &D_8015EF68);
            return;
        default:
            func_8015F768(actor, context, sprite, entity);
            return;
        }
    } else if (!(entity->flags & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(entity->flags & 0x430)) {

                if ((s16)dungeonCompareMonsterNeighborValues(sprite->position.tile.x,
                        sprite->position.tile.y, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    entity->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        sprite->position.tile.x,
                            sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
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
    anim_table = D_80161FB8;
    if (sprite->directionFrames == anim_table) {
        return;
    }
    sprite->directionFrames = anim_table;
    func_80047784(sprite,
        ((((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
