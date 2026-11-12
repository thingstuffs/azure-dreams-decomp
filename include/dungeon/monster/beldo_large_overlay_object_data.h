#ifndef DUNGEON_MONSTER_BELDO_LARGE_OVERLAY_OBJECT_DATA_H
#define DUNGEON_MONSTER_BELDO_LARGE_OVERLAY_OBJECT_DATA_H

#include "shared/object_node.h"

/* Object node slots at 0x80175D58; slot 1 is the named word at 0x80175D5C. */
extern ObjectNodeHeader *encounter_object_slots[];

/* The encounter overlay's object node pointer at 0x80175D5C. */
extern ObjectNodeHeader *encounter_overlay_object[];

#endif
