/* Relink of matched dungeon/func_80D3D7EC; every changed retail word is a paired relocation. */
#define D_80171A80 D_80165A80
#include "common.h"
#include "shared/dungeon_status.h"

extern u32 dungeonUpdateActorMovementToTile(void);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern void dungeonAdvanceStatusTimers(void *);
extern s32 dungeonCheckActorFloorTrap(void *, void *);

extern u8 D_80165A80[];

/* Updates actor behavior and state fields according to mode and input. */
void func_80166FEC(void *state, s32 unused, void *action_arg, void *actor_arg)
{
    void *action_data = action_arg;
    void *actor = actor_arg;

    if (dungeonUpdateActorMovementToTile() != 0) {
        if (*(u8 *)((u8 *)state + 0xB5) == 0) {
            dungeonReduceActorFoodMeter(actor, 4);
            dungeonAdvanceStatusTimers(actor);
            if ((dungeonCheckActorFloorTrap(action_data, actor) << 16) <= 0) {
                return;
            }
        } else {
            dungeonReduceActorFoodMeter(actor, 0x10);
            dungeonAdvanceStatusTimers(actor);
        }
        *(void **)((u8 *)state + 0x8C) = D_80165A80;
    }

    if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
        if (*(u8 *)((u8 *)state + 0xB5) != 0) {
            *(s16 *)((u8 *)state + 0x92) = 0;
        }
    }
}
