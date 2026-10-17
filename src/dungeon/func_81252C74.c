#include "common.h"
#include "shared/dungeon_status.h"



s32 dungeonAdvanceStatusTimers();
s32 dungeonUpdateActorMovementToTile();
void dungeonReduceActorFoodMeter();
s32 dungeonCheckActorFloorTrap();
extern s32 D_80171514;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in dungeonRunActorCallbacksAndAdjustGlobalFlag */

/* Runs actor callbacks, updates entity state on success, and applies the global flag adjustment. */
void dungeonRunActorCallbacksAndAdjustGlobalFlag(void *entity_ptr, s32 unused, s32 check_arg, s32 actor_arg)
{
    S_80172474_0 *entity = entity_ptr;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(actor, 0);
        dungeonAdvanceStatusTimers(actor);
        if ((dungeonCheckActorFloorTrap(check_value, actor) << 0x10) <= 0) {
            return;
        }
        do {
            entity->unk_8C = &D_80171514;
        } while (0);
    }
    if (dungeonStatus.flags & 0x80) {
        entity->unk_92 = -0x20;
    }
}
