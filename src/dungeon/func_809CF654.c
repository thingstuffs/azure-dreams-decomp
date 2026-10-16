/* Relink of matched dungeon/func_809C9654; every changed retail word is a paired relocation. */
#define D_80170E54 D_8016AE54
#define D_80173C7C D_8016DC7C
#define D_80173C84 D_8016DC84
#define D_80173CCC D_8016DCCC
#define D_80173CD4 D_8016DCD4
#define D_80173CDC D_8016DCDC
#define dungeonAdvanceStoredEntityPath func_8016B39C
#define advanceActorPathWithItemSearch func_8016B5F4
#define dungeonCheckActorTransitionAndStartEffect func_8016BDA0
#define dungeonStartDirectionalActorEffect func_8016BF64
#define func_8017207C func_8016C07C
#define func_80173A30 func_8016DA30
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

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
extern void func_8016B39C(void *, void *, void *, void *);
extern void func_8016B5F4(void *, void *, void *, void *);
extern s32 func_8016BDA0(void *, s32, void *, void *);
extern void func_8016BF64(void *, void *, void *, void *);
extern s32 func_8016C07C(void *, void *, void *, s32);
extern void func_8016DA30(void *, s32, void *, void *);

extern u8 D_8016AE54;
extern u8 D_8016DC7C[];
extern u8 D_8016DC84[];
extern u8 D_8016DCCC[];
extern u8 D_8016DCD4[];
extern u8 D_8016DCDC[];

typedef struct S_80170E54_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E54_2;   /* arg2 in func_8016AE54 */

/* Updates entity behavior, facing, and animation from dungeon and actor state. */
void func_8016AE54(void *controller, void *context, void *entity, EntityRec *actor_state)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8016B39C(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->tileY == 0) {
        dungeonAdvanceActorPendingAction(controller, context, entity, actor_state);
        if (((S_80170E54_2 *)entity)->unk_2C != D_8016DCDC) {
            u8 *early_table = D_8016DCD4;
            void *record = entity;
            entity = (u8 *)entity + 0x2C;
            *(void **)entity = early_table;
            func_80047784(record,
                early_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & 0x200) {
        if (((S_80170E54_2 *)entity)->unk_2C == D_8016DCDC) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(controller, context, entity, D_8016DCD4)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = D_8016DC7C;
            if (((S_80170E54_2 *)entity)->unk_2C != anim_table) {
                (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
                func_80047784(entity,
                    anim_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor_state->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(controller, context, entity, D_8016DC84)) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & 0x80000) {
            func_800AA888(controller, context, entity, actor_state);
            func_8016DA30(controller, context, entity, actor_state);
            return;
        }

        if ((s16)func_800A1C58(actor_state) != 0) {
            dungeonProcessSelectedActorRecord(controller, context, entity, actor_state);
        }
    }

    room_id = func_8009FB34(((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v);
    ((S_80170E54_2 *)entity)->unk_26 = room_id;

    if (actor_state->unk_6D > 0) {
        if (((u32)actor_state->flags1C) & 0x20) {
            func_800A9A0C(actor_state);
            return;
        }
        if (((S_80170E54_2 *)entity)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016B5F4(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(actor_state,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016C07C(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->unk_46 |= 0x4000;
            if (!(actor_state->unk_46 & 0x8000)) {
                func_8016B5F4(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)func_8016BDA0(controller, context, entity, actor_state) == 0) {
                func_8016BF64(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player_controller;
                s32 direction;

                direction = dungeonGetRoundedFacingAndRoundingFlag(
                    ((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_flags);
                player_controller = D_800814A8;
                actor_state->facing = direction;
                if (player_controller->unk_9A != 0x11) {
                    func_800A9A0C(actor_state);
                    return;
                }
                dungeonBeginActorSpellAction(controller, context, entity, D_8016DCCC, &D_8016AE54);
                return;
            }
        case 12:
            func_800A9A0C(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(controller, context, entity, D_8016DCCC, &D_8016AE54);
            return;
        default:
            break;
        }

        func_8016B5F4(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & 0x430)) {

                if ((s16)dungeonCompareMonsterNeighborValues(((S_80170E54_2 *)entity)->unk_24.at00.v,
                    ((S_80170E54_2 *)entity)->unk_24.at01.v, D_80082E80.tileX,
                    D_80082E80.tileY) != 0) {
                    actor_state->facing = dungeonGetRoundedFacingAndRoundingFlag(
                        ((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E54_2 *)entity)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_8016DC7C;
    if (((S_80170E54_2 *)entity)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
    func_80047784(entity,
        *(u8 *)((u32)(((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
