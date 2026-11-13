/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/person/object/object_entries_aliases.h"
#include "town/scene/event.h"
extern s8 D_800826B8;
extern s32 D_800CA0D4;
extern s32 D_800D64DC;



/*
 * Initializes entries from D_800D64DC, clears D_800826B8, and installs D_800CA0D4 with count ten
 * and angle 0x400.
 */
void init_mother_event_countdown(TownObjectRecord *object, s32 unused, SpriteFrameState *init_data) {
    initialize_object_entries((object), init_data, &D_800D64DC);
    D_800826B8 = 0;
    object->handler = &D_800CA0D4;
    object->timer = 0xA;
    object->heading = 0x400;
}
