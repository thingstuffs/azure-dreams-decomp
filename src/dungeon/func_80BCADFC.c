/* Relink of matched dungeon/func_80BEDE04; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource16_slot0.h"
extern void func_8016B9DC(void *, void *, void *, void *);

void func_8016E5FC(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor)) {
        state->callback = func_8016B9DC;
    }
}
