#include "common.h"
extern s32 update_actor_defeat_removal(void *, void *, void *, void *);
s32 func_80150FB8(void *state, void *position, void *packet, void *entity) { return update_actor_defeat_removal(state, position, packet, entity); }
