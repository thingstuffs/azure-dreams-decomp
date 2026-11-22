#include "modules/town_map_props.h"
#include "common.h"
#include "shared/dungeon_delay_views.h"
#include "shared/sprite_frame_state.h"
#include "town/map.h"
#include "engine/script.h"

/* Alternates the rendered mesh between the two indices supplied by the Yorozu prop table. */
void cycle_prop_output_values(YorozuMeshProp *record, ObjectPosition *unused_position, LitMeshSprite *output, s32 unused_value2)
{
    s16 state;
    const s32 *source;

    state = record->phase;
    source = record->mesh_indices;

    switch (state) {
    case 0:
        if (service_script_controller() == 0) {
            return;
        }
        if (check_town_target_and_callback(record) == 0) {
            return;
        }
        output->mesh_index = source[1];
        record->phase = record->phase + 1;
        return;
    case 1:
    case 3:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(record) == 0)) {
            record->phase = (record->phase + 1) & 3;
        }
        return;
    case 2:
        if (service_script_controller() == 0) {
            return;
        }
        if (check_town_target_and_callback(record) == 0) {
            return;
        }
        output->mesh_index = source[0];
        record->phase = record->phase + 1;
        return;
    }
}
