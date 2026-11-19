#ifndef TOWN_MENU_STATE_CALLBACKS_API_H
#define TOWN_MENU_STATE_CALLBACKS_API_H
#include "town/menu/object.h"
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct TownObject;
struct ObjectPosition;
struct LitMeshSprite;
void dispatch_menu_state_callback(void *obj, void *position, void *sprite);
void flag_inactive_object_or_run_callback(DoorDisplayBody *object, struct ObjectPosition *position, struct LitMeshSprite *mesh);

#endif
