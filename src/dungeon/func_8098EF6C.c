/* Relink of matched dungeon/func_80976F6C; every changed retail word is a paired relocation. */
#define D_801714D4 D_801594D4
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 dungeonAdvanceStatusTimers();
extern s32 dungeonUpdateActorMovementToTile();
extern s32 dungeonReduceActorFoodMeter();
extern s32 dungeonCheckActorFloorTrap();

extern s32 D_801594D4[];

/* Selects the state table after a successful target check and applies the flagged offset. */
void func_8015A76C(void *state, s32 unused, s32 source, s32 target) {
    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = D_801594D4;
            if (dungeonStatus.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
