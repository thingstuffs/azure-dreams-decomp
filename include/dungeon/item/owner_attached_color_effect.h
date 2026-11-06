#ifndef DUNGEON_ITEM_OWNER_ATTACHED_COLOR_EFFECT_H
#define DUNGEON_ITEM_OWNER_ATTACHED_COLOR_EFFECT_H

#include "common.h"

/* create_owner_attached_color_effect installs the two-phase tint updater. */
typedef struct OwnerAttachedColorBody {
    void *owner;
    u8 pad_04[4];
    u16 phase;
    u16 unk_0A;
    u16 ticks_left;
} OwnerAttachedColorBody;

#endif
