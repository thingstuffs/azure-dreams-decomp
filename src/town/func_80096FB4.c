/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
#include "slus.h"
#include "town.h"
extern s32 town_threshold_update_address;

void init_sound_threshold_action(s32 **record, ObjectPosition *unused_position, s32 setup_value) {
    SD_Call(0x512);
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(action_object_handler_table, (struct TownObjectRecord *)(record), (void *)(setup_value));
    *record = &town_threshold_update_address;
}
