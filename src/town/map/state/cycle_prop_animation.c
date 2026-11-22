#include "modules/town_map_props.h"
#include "common.h"
#include "shared/sprite_source.h"
#include "town/map/state.h"
#include "engine/script.h"

/* Advances sprite animation and cycles two animation entries as the script and object checks change. */
void cycle_prop_animation(YorozuToggleProp *record, ObjectPosition *unused_position, SpriteFrameState *value) {
    s16 state;

    advance_sprite_animation_and_textures(value);
    state = record->phase;
    switch (state) {
    case 0:
        if ((service_script_controller() != 0) && (check_town_target_and_callback(record) != 0)) {
            select_record_entry_and_value(value, record->sources[1], 0);
            record->phase++;
        }
        break;
    case 1:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(record) == 0)) {
            record->phase++;
        }
        break;
    case 2:
        if ((service_script_controller() != 0) && (check_town_target_and_callback(record) != 0)) {
            select_record_entry_and_value(value, record->sources[0], 0);
            record->phase++;
        }
        break;
    case 3:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(record) == 0)) {
            record->phase = 0;
        }
        break;
    }
}
