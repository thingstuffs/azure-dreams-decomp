#ifndef SHARED_ITEM_MENU_H
#define SHARED_ITEM_MENU_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Three signed parameters passed to the item-menu lifecycle handlers. */
typedef struct ItemMenuParameters {
    int field0;
    int field4;
    int field8;
} ItemMenuParameters;

/* Three-word item-menu scene state rooted at D_80110EB8. */
typedef struct ItemMenuSceneState {
    int unk0;
    int unk4;
    int unk8;
} ItemMenuSceneState;

/* Item-menu selection delay status, limit and counter words. */
typedef struct ItemMenuDelayState {
    int unk0;
    int unk4;
    int unk8;
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

#endif
