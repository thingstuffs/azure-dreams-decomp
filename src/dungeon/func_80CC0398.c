#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;

typedef struct S_set_map_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_set_map_0;   /* arg3 in set_map */


typedef struct S_80173B98_2 {
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
} S_80173B98_2;   /* arg2 in dungeonUpdateCreatureActionsAndAnimation */



void func_80047784(void *sprite, u8 frame, s32 mode);
s32 dungeonCheckEntityRelation(void *creature, s32 offset);
s8 func_8009FB34(u8 tile_x, u8 tile_y);
s32 dungeonCompareMonsterNeighborValues(u8 source_x, u8 source_y, u8 target_x, u8 target_y);
s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 func_800A1C58(void *creature);
void func_800A9A0C(void *creature);
void dungeonBeginPushedActorMove(void *actor, M2C_UNK context, void *sprite, void *creature);
s32 dungeonBeginReadyActorDirectionalAction(void *actor, M2C_UNK context, void *sprite, void *creature);
void dungeonAdvanceActorPendingAction(void *actor, M2C_UNK context, void *sprite, void *creature);
void func_800AA888(void *actor, M2C_UNK context, void *sprite, void *creature);
s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
void dungeonProcessSelectedActorRecord(void *actor, M2C_UNK context, void *sprite, void *creature);
void dungeonUpdateObjectOrSelectDirectionalData(void *actor, M2C_UNK context, void *sprite, void *creature);
void dungeonChooseHeadingAndAdvanceActor(void *actor, M2C_UNK context, void *sprite, void *creature);
void func_80174924(void);
s32 dungeonCheckObjectActionAndClearFlags(void *actor, M2C_UNK context, void *sprite, s32 value);
s32 dungeonSelectNearbyTargetAndStartAction(void *actor, M2C_UNK context, void *sprite, void *creature);

extern u8 D_80176320[];
extern M2C_UNK D_80176358;
extern M2C_UNK D_80176360;
extern M2C_UNK D_80176370;

static __inline__ void set_map(void *sprite, void *creature, u8 *direction_map) {
    (((S_80173B98_2 *)sprite)->unk_2C) = (void *)direction_map;
    func_80047784(sprite, direction_map[((s32) (gameWork.view.viewAngle + ((S_set_map_0 *)creature)->unk_2A + 0x100)
        >> 9) & 7], 0);
}

/* Updates dungeon creature actions, facing direction, and animation. */
void dungeonUpdateCreatureActionsAndAnimation(void *actor, M2C_UNK context, void *sprite, EntityRec *creature) {
    M2C_UNK direction_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_flags;

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        func_80174924();
        return;
    }
    if (creature->tileY == 0) {
        dungeonAdvanceActorPendingAction(actor, context, sprite, creature);
        if (((S_80173B98_2 *)sprite)->unk_2C == &D_80176360) {
            return;
        }
        set_map(sprite, creature, (u8 *)&D_80176358);
        return;
    }
    if (creature->flags1C & 0x200) {
        if (((S_80173B98_2 *)sprite)->unk_2C == &D_80176360) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (dungeonResetActorActionState(actor, context, sprite, &D_80176358) != 0) {
            return;
        }
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        if (creature->flags1C & 0x100) {
            dungeonBeginPushedActorMove(actor, context, sprite, creature);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 14) {
            if (((S_80173B98_2 *)sprite)->unk_2C != (void *)D_80176320) {
                set_map(sprite, creature, D_80176320);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (creature->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor, context, sprite, &D_80176370) != 0) {
                return;
            }
        }
        if (creature->flags1C & 0x80000) {
            func_800AA888(actor, context, sprite, creature);
            dungeonUpdateObjectOrSelectDirectionalData(actor, context, sprite, creature);
            return;
        }
        if ((func_800A1C58(creature) << 0x10) != 0) {
            dungeonProcessSelectedActorRecord(actor, context, sprite, creature);
        }
    }
    tile_index = func_8009FB34(((S_80173B98_2 *)sprite)->unk_24.at00.v, ((S_80173B98_2 *)sprite)->unk_24.at01.v);
    ((S_80173B98_2 *)sprite)->unk_26 = tile_index;
    if (creature->unk_6D > 0) {
        if (creature->flags1C & 0x20) {
            func_800A9A0C(creature);
            return;
        }
        if (((S_80173B98_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            dungeonChooseHeadingAndAdvanceActor(actor, context, sprite, creature);
            return;
        }
        if (!(creature->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((dungeonCheckEntityRelation(creature, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((dungeonCheckObjectActionAndClearFlags(actor, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = creature->unk_46 | 0x4000;
            creature->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                dungeonChooseHeadingAndAdvanceActor(actor, context, sprite, creature);
                return;
            }
        }
        switch (creature->unk_46 & 0x3FFF) {
        case 9:
            if (dungeonSelectNearbyTargetAndStartAction(actor, context, sprite, creature) != 0) {
                return;
            }
            dungeonChooseHeadingAndAdvanceActor(actor, context, sprite, creature);
            return;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 12:
            func_800A9A0C(creature);
            return;
        case 4:
        case 10:
        case 11:
        default:
            dungeonChooseHeadingAndAdvanceActor(actor, context, sprite, creature);
            return;
        }
    }
    status_flags = creature->flags1C;
    if (!(status_flags & 0x2000)) {
        if (tile_index >= 0 && (D_800E2970[tile_index].flags & 2)) {
        } else if (!(status_flags & 0x430)) {
            if ((dungeonCompareMonsterNeighborValues(((S_80173B98_2 *)sprite)->unk_24.at00.v, ((S_80173B98_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY) << 0x10) != 0) {
                creature->facing = dungeonGetRoundedFacingAndRoundingFlag(((S_80173B98_2 *)sprite)->unk_24.at00.v,
                    ((S_80173B98_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
            }
        }
    }
    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80173B98_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (((S_80173B98_2 *)sprite)->unk_2C == (void *)D_80176320) {
        return;
    }
    set_map(sprite, creature, D_80176320);
}
