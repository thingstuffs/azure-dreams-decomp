/* Relink of matched dungeon/func_80B48214; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource12_slot0.h"
extern void func_80158E54(void *, void *, void *, void *);

void func_8015B980(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = func_80158E54;
    }
}
