#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_object_and_play_sound(s32 **object, s32 unused, s32 context) {
    SD_Call(0x50B);
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0110, object, context);
    *object = (void *)update_actor_input_actions;
}
