/* Relink of matched dungeon/func_809CC43C; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource03_slot0.h"
extern void func_8014CE54(void *, void *, void *, void *);

void func_8014FC3C(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_8014CE54;
    }
}
