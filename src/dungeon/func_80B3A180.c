/* Relink of matched dungeon/func_80B48214; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource12_slot0.h"
extern void func_80152E54(void *, void *, void *, void *);

void func_80155980(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = func_80152E54;
    }
}
