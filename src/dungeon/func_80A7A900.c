/* Relink of matched dungeon/func_80A74900; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource07_slot0.h"
extern void func_8016AE54(void *, void *, void *, void *);

void func_8016E100(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = func_8016AE54;
    }
}
