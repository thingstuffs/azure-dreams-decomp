#ifndef DUNGEON_ITEM_SLOT_VIEW_MARKER_H
#define DUNGEON_ITEM_SLOT_VIEW_MARKER_H

#include "common.h"

/* Body allocated by create_slot_positioned_effect and advanced by its node callback. */
typedef struct SlotViewMarkerBody {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} SlotViewMarkerBody;

#endif
