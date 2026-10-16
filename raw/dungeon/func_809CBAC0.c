#include "common.h"

extern void func_800AD058(void *, void *, void *, void *);

/* Forward the resource callback to the resident service. */
void func_801732C0(void *state, void *motion, void *position, void *actor)
{
    func_800AD058(state, motion, position, actor);
}
