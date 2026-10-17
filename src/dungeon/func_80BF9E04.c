/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource16_slot0.h"
extern void func_80165014(void *, void *, void *, void *);

void func_80167604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor)) {
        state->callback = func_80165014;
    }
}
