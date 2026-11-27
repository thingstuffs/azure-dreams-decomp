#ifndef DUNGEON_ITEM_SLOT_VIEW_MARKER_H
#define DUNGEON_ITEM_SLOT_VIEW_MARKER_H

#include "common.h"

/* Body allocated by create_slot_positioned_effect and advanced by its node callback. */
typedef struct SlotViewMarkerBody {
    u16 state;
    u16 rest_angle;
    s16 turn_steps;
    u8 pad_06[2];
    s16 unk_08;
    s16 target_angle;
    s16 shake_timer;
    s16 base_z;
    s16 slot;
} SlotViewMarkerBody;

#endif
