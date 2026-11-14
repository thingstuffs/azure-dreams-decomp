#include "common.h"
#include "shared/entity_objects.h"
#include "town/person.h"
#include "town/person/state.h"
#include "town/person/motion.h"
#include "town/person/state_updates.h"





/* Initialize state and copy default values, adjusting the final output value. */
void initialize_person_state(void *state, void *output) {
    *(void **)((s8 *)state - 0x10) = update_person_view_and_record;
    fill_position_history();
    *(s16 *)((s8 *)state + 0x90) = 0;
    *(void **)((s8 *)state + 0x50) = move_person_toward_sample;
    *(s16 *)((s8 *)state + 0x6A) = 0;

    {
        *(u16 *)((s8 *)output + 2) = ((u16)view_reference_entity.x.w.i);
        *(u16 *)((s8 *)output + 6) = ((u16)view_reference_entity.y.w.i);
        *(s16 *)((s8 *)output + 0xA) = ((u16)view_reference_entity.z.w.i) - get_map_cell_step_size(output);
    }
}
