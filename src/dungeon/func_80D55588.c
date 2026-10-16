/* Relink of matched dungeon/func_80D3D588; every changed retail word is a paired relocation. */
#define dungeonBeginActorExclusiveAction func_8015DF44
#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"


extern s32 dungeonPrepareDirectionalAttack();
extern s32 func_800A2B5C();
extern void dungeonApplyCameraOffsetAndSelectTarget();
extern void func_8015DF44(void *, s32, s32, s32, s32);


/* Start the actor action and reset its state when ready, or dispatch the alternate action. */
void func_8015AD88(Rec_func_800A9E70_arg0 *state, s32 world_pos, s32 tile_pos, EntityRec *actor)
{
    if (state->unk_B5 == 0) {
        actor->unk_71 &= 0x7F;
        if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 16) == 0)) {
            dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, world_pos, 8, 0x300);
            if ((func_800A2B5C(actor) << 16) == 0) {
                state->unk_8C = 0;
                state->unk_9A.as_s8 = 0x11;
                state->unk_9B.as_s8 = 0;
                state->unk_96.as_s16 = 0;
                actor->unk_6D--;
                state->unk_98 |= 8;
                dungeonPrepareDirectionalAttack(actor, tile_pos, actor->facing, 1, 0);
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
                return;
            }
        }
    } else {
        func_8015DF44(state, world_pos, tile_pos, 1, 1);
    }
}
