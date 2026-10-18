#include "modules/dungeon_ovl_16b08_local.h"

void initialize_actor_position_interaction_action(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra) {
    object->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0130, object, context);
    object->unk_00.as_pm = (void *)update_actor_position_and_interaction;
}
