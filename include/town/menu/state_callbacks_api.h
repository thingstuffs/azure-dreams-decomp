#ifndef TOWN_MENU_STATE_CALLBACKS_API_H
#define TOWN_MENU_STATE_CALLBACKS_API_H
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct TownObject;
void dispatch_menu_state_callback(void *obj, void *position, void *sprite);
void flag_inactive_object_or_run_callback(struct TownObject *object, s32 unused, u8 *output);

#endif
