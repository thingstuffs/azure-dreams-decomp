#include "common.h"

s32 func_80044724(void)
{
    struct S_80083178 *source;
    struct S_80083178State *saved;

    source = &D_80083178;
    saved = &D_80083CE8;

    if (source->state_94.v[0].x != saved->v[0].x) goto update;
    if (source->state_94.v[0].y != saved->v[0].y) goto update;
    if (source->state_94.v[0].z != saved->v[0].z) goto update;
    if (source->state_94.v[1].x != saved->v[1].x) goto update;
    if (source->state_94.v[1].y != saved->v[1].y) goto update;
    if (source->state_94.v[1].z != saved->v[1].z) goto update;
    if (source->state_94.v[2].x != saved->v[2].x) goto update;
    if (source->state_94.v[2].y != saved->v[2].y) goto update;
    if (source->state_94.v[2].z != saved->v[2].z) goto update;
    if (source->state_94.v[3].x != saved->v[3].x) goto update;
    if (source->state_94.v[3].y != saved->v[3].y) goto update;
    if (source->state_94.v[3].z == saved->v[3].z) goto equal;

update:
    D_80083CE8.v[0] = source->state_94.v[0];
    D_80083CE8.v[1] = source->state_94.v[1];
    D_80083CE8.v[2] = source->state_94.v[2];
    D_80083CE8.v[3] = source->state_94.v[3];
    return 1;

equal:
    return 0;
}
