#include "common.h"
#include "town/scene/flags.h"
#include "town/data.h"
#include "town/scene/score_sprite_data.h"

/* Set record and global flags when the record is zero and linked flag 8 is set. */
void set_record_flags_when_linked(RisingScoreTextDisplay *record) {
    TownScoreCounterView *controller = record->controller;
    if (record->state == 0) {
        if (controller->flags & 8) {
            u16 *flags = &NODE_HEADER(record)->flags;
            *flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
    }
}
