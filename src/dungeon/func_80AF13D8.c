#include "modules/dungeon_resource10_slot0.h"

void func_80172BD8(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);
        if ((dungeonCheckActorFloorTrap(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = ((void *)func_801717F4);
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
