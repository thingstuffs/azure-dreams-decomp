#include "modules/dungeon_ovl_16b08_local.h"

void func_800943B8(Rec_func_80094268_arg0 *object, s32 setup_arg, s32 context, s32 setup_extra) {
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0108, object, context);
    object->unk_00.as_pm = (void *)update_actor_movement_actions;
    object->unk_0A.as_s16 = 6;
}
