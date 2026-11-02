#ifndef TOWN_MENU_STATE_H
#define TOWN_MENU_STATE_H
/* Prototypes of the functions defined in src/town/menu/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/item_menu.h"

struct SpriteFrameState;
struct CatalogDisplay;
struct S_800A24A8_0;
struct S_800A24A8_1;
struct TownObject;

/* initialize_item_menu_state.c */
void initialize_item_menu_state(ItemMenuObject *object, ItemMenuStateNode *owner);

void initialize_indexed_render_state(void *object, ObjectPosition *unused, struct SpriteFrameState *render_state);

#endif
