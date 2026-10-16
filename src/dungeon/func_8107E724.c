/* Relink of matched dungeon/func_8105A724; every changed retail word is a paired relocation. */
#define D_80173FB8 D_8014FFB8
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"


void func_80047784(void *, u8, s32);
void dungeonPrepareDirectionalAttack(void *, void *, s16, s32, s32);
s32 dungeonGetActorHeightDifference(s32, void *);
s32 dungeonPlaceActorAtDirectionalNeighbor(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void dungeonApplyCameraOffsetAndSelectTarget(void *, s32, s32, s32);
extern u8 D_8014FFB8[];

/* Checks action eligibility and updates the actor state and directional animation on success. */
s32 func_8014DF24(void *action_state, s32 action_id, void *sprite, EntityRec *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    s32 target_direction;
    u16 status_flags;
    u16 state_flag;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    target_direction = dungeonPlaceActorAtDirectionalNeighbor(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25, actor->facing);

    if ((((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)
        ? target_direction == 0
        : (func_800A2CB8(actor, target_direction) << 0x10) == 0) {
        return 0;
    }

    status_flags = dungeonStatus.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000)) {
        if (status_flags & 8) {
            return -1;
        }
    }

    if ((u32)(((0 - dungeonGetActorHeightDifference(target_direction, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 0x10) != 0) {
        return -1;
    }

    dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 0x10) != 0) {
        return -1;
    }
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
    actor->unk_84 = 0x7C;
    actor->unk_85 = 0;
    state_flag = ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000;
    if (state_flag) {
        /* retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
        target_direction = 0;
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_8014FFB8;
    func_80047784(sprite,
        D_8014FFB8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
    dungeonPrepareDirectionalAttack(actor, sprite, actor->facing, 1, 0);
    return 1;
}
