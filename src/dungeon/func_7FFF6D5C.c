#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_object_with_counter(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    SD_Call(0x511);
    call_the_handler_selects_nonzero_entry(&D_800D0120, object, context);
    object->unk_00.as_pm = (void *)update_actor_with_interaction_state;
    object->unk_0A.as_s16 = 6;
}
