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

struct DoorTransitionEffect;

/* The door quad constructor stores its effect and a child index in the body of
 * each flag-0x136 node. Its first update selects the orbit and color table rows. */
typedef struct DoorProjectionChild {
    void (*update)(struct DoorProjectionChild *, struct ObjectPosition *, struct SpriteFrameState *);
    u8 pad_04[12];
    struct DoorTransitionEffect *parent;
    u8 pad_14[12];
    s16 index;
    s16 matrix_index;
    s32 x, y, z;
    u8 pad_30[12];
    u32 color_flags; /* Low three bytes select full intensity for red, green and blue. */
} DoorProjectionChild;

void initialize_indexed_render_state(DoorProjectionChild *object, ObjectPosition *unused, struct SpriteFrameState *render_state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct CatalogDisplay;
void initialize_catalog_state(struct CatalogDisplay *state);

#endif
