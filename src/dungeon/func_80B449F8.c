#include "modules/dungeon_resource12_slot0.h"

void func_801721F8(R12_801721F8_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (dungeonUpdateActorMovementToTile(state, context, source, target) != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)func_80170E70);
        state->unk_90.at00.v = 0;
    }
    if (dungeonStatus.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
