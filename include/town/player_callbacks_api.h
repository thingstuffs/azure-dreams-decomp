#ifndef TOWN_PLAYER_CALLBACKS_API_H
#define TOWN_PLAYER_CALLBACKS_API_H
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/entity.h"
void advance_player_toward_target(void *state_arg, ObjectPosition *motion, void *context);

#endif
