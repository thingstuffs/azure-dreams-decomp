#include "common.h"
#include "town/scene/score_sprite_data.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

/* Processes a state-zero record and sets record/global flags if its linked record has bit 3 set. */
void update_number_display_record(RisingScoreTextDisplay *record) {
    u16 *flags;
    TownScoreCounterView *linked_record;

    linked_record = record->controller;
    if (record->state == 0) {
        func_80058588(*record->value, func_80071424(record->text),
            record->text);
        if (linked_record->flags & 8) {
            flags = &NODE_HEADER(record)->flags;
            *flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
    }
}
