#include "modules/dungeon_resource06_slot0.h"

void func_80172694(void *state, s32 unused, s32 source, s32 target) {
    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)func_8017140C);
            if (dungeonStatus.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
