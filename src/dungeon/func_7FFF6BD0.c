#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_object_type_six(Rec_func_80094268_arg0 *object) {
    call_the_handler_selects_nonzero_entry(&D_800D00C0, object);
    object->unk_00.as_pm = (void *)update_countdown_and_fallback;
    object->unk_0A.as_s16 = 6;
}
