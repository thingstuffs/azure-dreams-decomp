#include "common.h"

extern s32 dungeonUpdateActorMovementToTile(void);
extern void dungeonReduceActorFoodMeter(s32, s32);
extern void dungeonAdvanceStatusTimers(s32);
extern s32 dungeonCheckActorFloorTrap(s32, s32);
extern s32 D_80171728;

/* Updates the actor and resets the entity state when the checks succeed. */
void dungeonResetEligibleEntityState(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);
        if ((dungeonCheckActorFloorTrap(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = &D_80171728;
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
