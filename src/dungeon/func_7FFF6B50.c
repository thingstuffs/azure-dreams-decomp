#include "modules/dungeon_ovl_16b08_local.h"

void initialize_actor_action_state(Rec_func_80094268_arg0 *object, EntityRec *state, M2C_UNK setupArg) {
    dispatch_sound_by_global_flag();
    state->flags14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(&D_800D00B0, object, setupArg);
    object->unk_00.as_pm = (void *)update_actor_and_dispatch_state;
    object->unk_0A.as_s16 = 0;
}
