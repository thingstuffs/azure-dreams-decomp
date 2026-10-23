#ifndef SHARED_ITEM_MENU_H
#define SHARED_ITEM_MENU_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Three signed parameters passed to the item-menu lifecycle handlers. */
/* Leading work words of an item-menu object allocated by create_item_menu_object.
 * start_item_menu_object_processing passes them to the menu reset and child-release handlers. */
typedef struct ItemMenuParameters {
    int field0; /* primary menu object header passed to the retirement/reset handler */
    int field4; /* child object header scheduled for linked-entry release, or zero */
    int field8; /* auxiliary display object whose update callback is replaced for completion */
} ItemMenuParameters;

/* Three-word item-menu scene state rooted at D_80110EB8. */
/* Town item-menu scene request words rooted at item_menu_scene_state.
 * The state-selection wrappers store the request value and select phases 3, 5 or 7. */
typedef struct ItemMenuSceneState {
    int unk0;
    int unk4;
    int unk8; /* menu scene phase; the request wrappers set 3, 5 or 7 */
} ItemMenuSceneState;

/* Item-menu selection delay status, limit and counter words. */
/* Caller-owned item-menu selection-delay work, updated by tick_item_menu_selection_delay.
 * The cursor transition runs before the counter advances and the delay status is cleared. */
typedef struct ItemMenuDelayState {
    int unk0; /* selection-delay status, cleared when the prior counter reaches the limit */
    int unk4; /* selection-delay duration and interpolation denominator, in update ticks */
    int unk8; /* elapsed selection-delay updates; incremented once per tick */
} ItemMenuDelayState;

/* Signed enable word at +0x1C of the item-menu referenced state. */
typedef struct ItemMenuEnabledView {
    unsigned char pad_00[0x1C];
    int unk_1C;
} ItemMenuEnabledView;

/* Signed flag word at +0x1C of the shop record. */
typedef struct ItemMenuFlagsView {
    unsigned char pad_00[0x1C];
    int unk_1C;
} ItemMenuFlagsView;

/* Screen position record of one item-menu display part. */
typedef struct ItemMenuPartPosition {
    unsigned char pad_00[0x8];
    short x; /* horizontal screen offset */
    short y; /* vertical screen offset */
} ItemMenuPartPosition;

/* One item-menu display part. The item-menu object keeps a pointer to an array of 40 part
 * pointers at +0xA8 (allocated by load_actor_display_resource): parts 0-3 are the panel slots,
 * 4 and 5 the selection cursor pair, 6-35 the item rows, 38 and 39 the side indicators. */
typedef struct ItemMenuPart {
    void *handler; /* slot handler or owning panel block */
    ItemMenuPartPosition *position;
} ItemMenuPart;

#endif
