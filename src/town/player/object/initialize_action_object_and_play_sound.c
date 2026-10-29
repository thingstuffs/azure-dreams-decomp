#include "common.h"
#include "shared/town_handler_entries.h"
#include "slus.h"
#include "town/player/input.h"
#include "town/player/object.h"
#include "town/player/call_the_handler_selects_nonzero_entry_api.h" /* extern */
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                  /* extern */
#include "shared/entity.h"

/* Reset and initialize the record, then assign its handler. */
void initialize_action_object_and_play_sound(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x50B);
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D0110, (struct Rec_func_80094268_arg0 *)(record), (void *)(setup_value));
    *record = &update_actor_input_actions;
}
