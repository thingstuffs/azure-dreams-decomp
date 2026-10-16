#include "modules/dungeon_resource08_slot0.h"

void func_801723C4(R08_801723C4_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (dungeonUpdateActorMovementToTile(state, context, source, target) != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)dungeonUpdateActorBehaviorAndEffect);
        state->unk_90.at00.v = 0;
    }
    if (dungeonStatus.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
