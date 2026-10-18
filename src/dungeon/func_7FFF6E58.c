#include "modules/dungeon_ovl_16b08_local.h"

void initialize_input_driven_scene_object(s32 **outputSlot, EntityRec *state, s32 initContext) {
    dispatch_sound_by_global_flag();
    state->flags14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(&D_800D0140, outputSlot, initContext);
    *outputSlot = (void *)update_town_object_from_input;
}
