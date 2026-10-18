#include "modules/dungeon_ovl_1831370.h"

void initialize_embedded_object_state(void *state, s32 parent, s32 type, s32 config) {
    initialize_object_phase_data(state, parent, type, config);
    initialize_owner_defaults(state, state + 0x60, state + 0x38, state + 0x48);
    initialize_object_destination_fields(state, ((ovl_1831370_818119A0_S_800269A0_0 *)state)->unk_70);
}
