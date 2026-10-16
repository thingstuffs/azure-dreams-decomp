#include "modules/dungeon_resource08_slot0.h"

void dungeonAdvanceATimedActorAnimationAppliesCompletionEffects(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateLinkedActorMotion(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = dungeonUpdateActorBehaviorAndEffect;
        }
    }
}
