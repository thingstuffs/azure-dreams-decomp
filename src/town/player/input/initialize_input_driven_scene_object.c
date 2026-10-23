#include "common.h"
#include "shared/entity.h"
#include "shared/town_handler_entries.h"

void dispatch_sound_by_global_flag(void);                            /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h" /* extern */
extern s32 town_input_object_address;


/* Initialize state and set the output pointer to the shared data. */
void initialize_input_driven_scene_object(s32 **outputData, ObjectPosition *state, s32 setupValue) {
    dispatch_sound_by_global_flag();
    state->velocity_z = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(D_800D0140, (struct Rec_func_80094268_arg0 *)(outputData), (void *)(setupValue));
    *outputData = &town_input_object_address;
}
