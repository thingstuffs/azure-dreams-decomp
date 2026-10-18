#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_object(M2C_UNK **object) {
    call_the_handler_selects_nonzero_entry(&D_800D00B8, object);
    *object = (void *)update_threshold_bound_object;
}
