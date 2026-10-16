/* Relink of matched dungeon/func_80B988DC; every changed retail word is a paired relocation. */
#define D_80170E9C D_80158E9C
#include "common.h"

extern s32 dungeonUpdateActorMovementToTile(M2C_UNK);
extern void dungeonReduceActorFoodMeter(s32, s32);
extern void dungeonAdvanceStatusTimers(s32);
extern s32 dungeonCheckActorFloorTrap(s32, s32);
extern s32 D_80158E9C;

/* Updates an eligible actor and conditionally resets the entity state. */
void func_8015A0DC(void *entity_arg, s32 check_context, s32 value_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = value_arg;
    s32 actor = actor_arg;

    if (dungeonUpdateActorMovementToTile(entity_arg, check_context, value_arg, actor_arg) != 0) {
        dungeonReduceActorFoodMeter(actor, 3);
        dungeonAdvanceStatusTimers(actor);
        if ((dungeonCheckActorFloorTrap(check_value, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80158E9C;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
