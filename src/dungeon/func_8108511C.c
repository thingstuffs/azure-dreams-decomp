#include "common.h"

extern s32 dungeonUpdateActorMovementToTile(void *, s32, s32, s32);
extern void dungeonReduceActorFoodMeter(s32, s32);
extern void dungeonAdvanceStatusTimers(s32);
extern s32 dungeonCheckActorFloorTrap(s32, s32);
extern s32 D_80170E94;

/* Update the actor after a successful action and reset the entity script on a positive result. */
void dungeonFinishSuccessfulActorAction(void *action_entity, s32 action, s32 source_actor, s32 target_actor) {
    void *entity = action_entity;
    s32 source = source_actor;
    s32 actor = target_actor;

    if (dungeonUpdateActorMovementToTile(action_entity, action, source_actor, target_actor) != 0) {
        dungeonReduceActorFoodMeter(actor, 5);
        dungeonAdvanceStatusTimers(actor);
        if ((dungeonCheckActorFloorTrap(source, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E94;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
