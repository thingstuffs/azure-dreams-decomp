/* Relink of matched dungeon/func_80B43670; every changed retail word is a paired relocation. */
#define D_80170E70 D_8016AE70
#define D_80175A54 D_8016FA54
#define D_80175A5C D_8016FA5C
#define D_80175A8C D_8016FA8C
#define D_80175A94 D_8016FA94
#define D_80175A9C D_8016FA9C
#define func_801713D4 func_8016B3D4
#define func_8017162C func_8016B62C
#define func_80171DD8 func_8016BDD8
#define dungeonSelectAndStartTargetAction func_8016BF9C
#define func_801720B4 func_8016C0B4
#define func_80173D64 func_8016DD64
#define func_8017526C func_8016F26C
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern void func_80047784(void *, u8, s32);
extern s32 dungeonCheckEntityRelation(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 dungeonCompareMonsterNeighborValues(u8, u8, u8, u8);
extern s16 dungeonGetRoundedFacingAndRoundingFlag();
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8016B3D4(void *, void *, void *, void *);
extern void func_8016B62C(void *, void *, void *, void *);
extern s32 func_8016BDD8(void *, s32, void *, void *);
extern void func_8016BF9C(void *, void *, void *, void *);
extern s32 func_8016C0B4(void *, void *, void *, s32);
extern void func_8016DD64(void *, s32, void *, void *);
extern void func_8016F26C(void *, s32, s32, void *);

extern u8 D_8016AE70[];
extern u8 D_8016FA54[];
extern u8 D_8016FA5C[];
extern u8 D_8016FA8C[];
extern u8 D_8016FA94[];
extern u8 D_8016FA9C[];


typedef struct S_80170E70_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x66];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170E70_0;   /* arg0 in func_8016AE70 */

typedef struct S_80170E70_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E70_1;   /* arg3 in func_8016AE70 */

typedef struct S_80170E70_2 {
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
    void * unk_2C;
} S_80170E70_2;   /* arg2 in func_8016AE70 */



/* Update the actor's dungeon behavior, facing, and animation for its current state. */
void func_8016AE70(void *entity, void *context, void *sprite, void *actor)
{
    u8 *effect_table;
    s32 next_state;
    s16 path_distance;
    s16 target_angle;
    s32 actor_flags;
    s32 action_index;
    s8 tile_id;
    s32 current_state;
    u16 action_flags;
    EntityRec *owner;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80170E70_0 *)entity)->unk_9A = 14;
        func_8016B3D4(entity, context, sprite, actor);
        return;
    }


    if (((S_80170E70_1 *)actor)->unk_25 == 0) {
        dungeonAdvanceActorPendingAction(entity, context, sprite, actor);
        if (((S_80170E70_2 *)sprite)->unk_2C == D_8016FA9C) {
            return;
        }
        {
            u8 *effects = D_8016FA94;
            (*(void * *)((u8 *)sprite + (0x2C))) = effects;
            func_80047784(
                sprite,
                effects[((gameWork.view.viewAngle + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((S_80170E70_2 *)sprite)->unk_2C == D_8016FA9C) {
            ((S_80170E70_0 *)entity)->unk_9A = 13;
            ((S_80170E70_0 *)entity)->unk_9B = 1;
            ((S_80170E70_0 *)entity)->unk_8C = 0;
            ((S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(entity, context, sprite, D_8016FA94) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((S_80170E70_1 *)actor)->unk_1C & 0x100) {
            dungeonBeginPushedActorMove(entity, context, sprite, actor);
            return;
        }

        current_state = ((S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = D_8016FA54;

            if (((S_80170E70_2 *)sprite)->unk_2C != effect) {
                (*(void * *)((u8 *)sprite + (0x2C))) = effect;
                func_80047784(
                    sprite,
                    effect[((gameWork.view.viewAngle + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((S_80170E70_1 *)actor)->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(entity, context, sprite, D_8016FA5C) != 0) {
                return;
            }
        }

        if (((S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            func_800AA888(entity, context, sprite, actor);
            func_8016DD64(entity, context, sprite, actor);
            return;
        }

        if ((s16)func_800A1C58(actor) != 0) {
            if ((s16)dungeonProcessSelectedActorRecord(entity, context, sprite, actor) != 0) {
                func_8016F26C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = func_8009FB34(((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v);
    ((S_80170E70_2 *)sprite)->unk_26 = tile_id;

    if (((S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((S_80170E70_1 *)actor)->unk_1C & 0x20) {
            func_800A9A0C(actor);
            return;
        }
        if (((S_80170E70_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016B62C(entity, context, sprite, actor);
            return;
        }

        action_flags = ((S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(
                        actor, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016C0B4(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8016B62C(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_8016BDD8(entity, context, sprite, actor) != 0) {
                return;
            }
            func_8016BF9C(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = dungeonGetRoundedFacingAndRoundingFlag(
                ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &path_distance);
            owner = D_800814A8;
            ((S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(entity, context, sprite, D_8016FA8C, D_8016AE70);
                return;
            }

        case 11:
            func_800A9A0C(actor);
            return;

        case 0:
        case 1:
        case 2:
            dungeonBeginActorSpellAction(entity, context, sprite, D_8016FA8C, D_8016AE70);
            return;

        default:
            func_8016B62C(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((D_800E2970[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)dungeonCompareMonsterNeighborValues(
                        ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    ((S_80170E70_1 *)actor)->unk_2A = dungeonGetRoundedFacingAndRoundingFlag(
                        ((S_80170E70_2 *)sprite)->unk_24.at00.v, ((S_80170E70_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &path_distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E70_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    effect_table = D_8016FA54;
    if (((S_80170E70_2 *)sprite)->unk_2C == effect_table) {
        return;
    }
    {
        u8 *effects = effect_table;
        (*(void * *)((u8 *)sprite + (0x2C))) = effects;
        func_80047784(
            sprite,
            effects[((gameWork.view.viewAngle + ((S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
}
