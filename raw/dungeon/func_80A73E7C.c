#include "common.h"

extern void func_800AB538(void *, void *, void *, void *);

/* Forward the resource callback to the resident service. */
void func_8017367C(void *state, void *motion, void *position, void *actor)
{
    func_800AB538(state, motion, position, actor);
}
