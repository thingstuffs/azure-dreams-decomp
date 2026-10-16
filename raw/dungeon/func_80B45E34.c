#include "common.h"

extern void func_800AB778(void *, void *, void *, void *);

/* Forward the resource callback to the resident service. */
void func_80173634(void *state, void *motion, void *position, void *actor)
{
    func_800AB778(state, motion, position, actor);
}
