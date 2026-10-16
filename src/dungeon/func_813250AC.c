#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
typedef struct Ent Ent;

/* cfail-repair: tf7-phase1-cache-v3 */
Ent *dungeonPrepareDirectionalAttack(); /* extern */
s32 func_800A2B5C();                          /* extern */


/* Clear the actor flag and update its action state when both checks pass. */
void dungeonClearActorFlagAndAdvanceAction(Rec_func_800A9E70_arg0 *action_state, s32 action_context, void *effect_context,
    EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_9B.as_s8 = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            dungeonPrepareDirectionalAttack(actor, effect_context, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 6;
        }
    }
}
