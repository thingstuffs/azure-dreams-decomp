#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171A80_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; u8 v; } unk_9A;   /* accessed as both */
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xC];
    union { u8 v; u8 n; } unk_B0;   /* accessed as both */
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80171A80_0;   /* arg0 in dungeonUpdateActorTurnAndAction */


typedef struct S_80171A80_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171A80_2;   /* arg2 in dungeonUpdateActorTurnAndAction */


typedef struct S_80171A80_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80171A80_6;   /* global in dungeonUpdateActorTurnAndAction */


extern void func_80047784(void *, s32, s32);
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
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void dungeonResetActionAndDecrementActorCount(void *, void *, void *, void *);
extern void createOwnerLinkedDirectionalObject(void *, void *, void *);
extern void dungeonPrepareActorDirectionalAction(u8 *entity, s32 action_param, u8 *action_sprite, u8 *frame_table, s32 fallback_state);
extern void dungeonAdvanceAuraActorTurnPath(void *, void *, void *, void *);
extern void dungeonChooseAndExecuteActorStep(void *work_data, void *action_context, u8 *position, u8 *actor);
extern s32 dungeonTryTurnActorTowardTarget(void *, void *, void *, void *);
extern void dungeonBeginActorAction(void *, void *, void *, void *);
extern s32 func_80172EA8(void *, void *, void *, s32);
extern void dungeonUpdateActorActionTransition(void *, void *, void *, void *);
extern void dungeonCompleteActorAction(void *, void *, void *, void *);
extern void dungeonBeginActorExclusiveAction(void *, void *, void *, s32, s32);

extern u8 D_800E23E0[];
extern u8 D_800E23F8[];
extern u8 D_800E2418[];
extern u8 D_800E2420[];
extern u8 D_800E2428[];
extern u8 D_80171A80[];

/* Updates dungeon actor animation, status, and action dispatch. */
void dungeonUpdateActorTurnAndAction(void *entity, void *context, void *sprite, EntityRec *actor)
{
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80171A80_0 *)entity)->unk_9A.n = 0xE;
        dungeonAdvanceAuraActorTurnPath(entity, context, sprite, actor);
        return;
    }

    if (actor->tileY == 0) {
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table;

            dungeonAdvanceActorPendingAction(entity, context, sprite, actor);
            if (((S_80171A80_2 *)sprite)->unk_2C == D_800E2428) {
                return;
            }
            anim_table = D_800E2420;
            (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                ((u8 *)anim_table)[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        } else {
            dungeonBeginActorExclusiveAction(entity, context, sprite, 0, 0);
            return;
        }
    }

    if (((u32)actor->flags1C) & 0x200) {
        if (((S_80171A80_2 *)sprite)->unk_2C == D_800E2428) {
            ((S_80171A80_0 *)entity)->unk_9A.n = 0xD;
            ((S_80171A80_0 *)entity)->unk_9B = 1;
            ((S_80171A80_0 *)entity)->unk_8C = 0;
            actor->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (dungeonResetActorActionState(entity, context, sprite, D_800E2420) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)actor->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(entity, context, sprite, actor);
            return;
        }

        if (((S_80171A80_0 *)entity)->unk_9A.v != 0xE) {
            ((S_80171A80_0 *)entity)->unk_9A.v = 0xE;
        }
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table = D_800E23E0;
            u8 is_active;

            if (((S_80171A80_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                func_80047784(sprite,
                    ((u8 *)anim_table)[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
                ((S_80171A80_2 *)sprite)->unk_05 = 1;
                is_active = ((S_80171A80_0 *)entity)->unk_B0.v;
                ((S_80171A80_0 *)entity)->unk_9E = 0;
                ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            } else {
                is_active = ((S_80171A80_0 *)entity)->unk_B0.n;
            }
            if (is_active == 0) {
                createOwnerLinkedDirectionalObject(entity, context, sprite);
            }
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                actor->flags1C |= 0x40000;
                ((S_80171A80_0 *)entity)->unk_98 &= 0xFFF7;
            }
        }

        if (actor->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(entity, context, sprite, D_800E23F8) != 0) {
                return;
            }
        }

        if (((u32)actor->flags1C) & 0x80000) {
            s16 height_delta;

            func_800AA888(entity, context, sprite, actor);
            height_delta = ((S_80171A80_0 *)entity)->unk_92.u - ((S_80171A80_0 *)entity)->unk_A2.u;
            ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            ((S_80171A80_0 *)entity)->unk_9E = 0;
            ((S_80171A80_0 *)entity)->unk_92.s = height_delta;
            dungeonUpdateActorActionTransition(entity, context, sprite, actor);
            return;
        }

        if ((func_800A1C58(actor) << 16) != 0) {
            dungeonProcessSelectedActorRecord(entity, context, sprite, actor);
        }
    }

    room_id = func_8009FB34(((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v);
    ((S_80171A80_2 *)sprite)->unk_26 = room_id;

    if (actor->unk_6D > 0) {
        if (((u32)actor->flags1C) & 0x20) {
            func_800A9A0C(actor);
            return;
        }
        if (((S_80171A80_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            dungeonChooseAndExecuteActorStep(entity, context, sprite, actor);
            return;
        }
        if (!(actor->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((dungeonCheckEntityRelation(actor,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172EA8(entity, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = actor->unk_46 | 0x4000;
            actor->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                dungeonChooseAndExecuteActorStep(entity, context, sprite, actor);
                return;
            }
        }

        action_state = actor->unk_46 & 0x3FFF;
        switch (action_state) {
        case 8:
            if ((dungeonTryTurnActorTowardTarget(entity, context, sprite, actor) << 16) != 0) {
                return;
            }
            dungeonBeginActorAction(entity, context, sprite, actor);
            return;

        case 9:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                dungeonCompleteActorAction(entity, context, sprite, actor);
                return;
            }
            dungeonBeginActorExclusiveAction(entity, context, sprite, 1, 0);
            return;

        case 10:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                dungeonResetActionAndDecrementActorCount(entity, context, sprite, actor);
                return;
            }
            dungeonBeginActorExclusiveAction(entity, context, sprite, 1, 0);
            return;

        case 5:
        case 6:
        case 7:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                EntityRec *player;
                s16 facing;

                facing = dungeonGetRoundedFacingAndRoundingFlag(
                    ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                actor->facing = facing;
                if (player->unk_9A == 0x11) {
                    goto coords_continue;
                }
            } else {
                goto global_continue;
            }

        case 12:
            func_800A9A0C(actor);
            return;

coords_continue:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                dungeonPrepareActorDirectionalAction(entity, context, sprite, D_800E2418, D_80171A80);
                return;
            }
global_continue:
            {
                void *leader = D_800E3D7C;

                if (((S_80171A80_6 *)leader)->unk_A6 != 0) {
                    dungeonChooseAndExecuteActorStep(entity, context, sprite, actor);
                    return;
                }
                ((S_80171A80_6 *)leader)->unk_A6 = 2;
                dungeonBeginActorExclusiveAction(entity, context, sprite, 1, 2);
                return;
            }

        case 2:
        case 1:
        case 3:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                dungeonBeginActorSpellAction(entity, context, sprite, D_800E2418, D_80171A80);
                return;
            } else {
                s32 action_mode = 1;

                dungeonBeginActorExclusiveAction(entity, context, sprite,
                    1, action_mode);
                return;
            }

        case 11:
        default:
            dungeonChooseAndExecuteActorStep(entity, context, sprite, actor);
            return;
        }
    }

    if (!(((u32)actor->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & 0x430)) {

                if ((dungeonCompareMonsterNeighborValues(
                        ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    actor->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }
}
