#ifndef TOWN_MENU_STATE_H
#define TOWN_MENU_STATE_H
#include "town/menu/object.h"
/* Prototypes of the functions defined in src/town/menu/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/item_menu.h"

struct SpriteFrameState;
struct CatalogDisplay;
struct LitMeshSprite;
void copy_negated_menu_phase(DoorDisplayBody *source, ObjectPosition *unused, struct LitMeshSprite *mesh);
struct TownObject;

/* initialize_item_menu_state.c */
void initialize_item_menu_state(ItemMenuObject *object, ItemMenuStateNode *owner);

void initialize_indexed_render_state(void *object, ObjectPosition *unused, struct SpriteFrameState *render_state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct CatalogDisplay;
void initialize_catalog_state(struct CatalogDisplay *state);

#endif
