#ifndef DUNGEON_MENU_CALLBACKS_API_H
#define DUNGEON_MENU_CALLBACKS_API_H

#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct InactiveTypeTwelveObjectBody;
struct ObjectPosition;
struct SpriteFrameState;
void update_dungeon_menu_object(u8 *object);
void update_viewport_transition(struct InactiveTypeTwelveObjectBody *transition, struct ObjectPosition *center, struct SpriteFrameState *render_params, int *context);

#endif
