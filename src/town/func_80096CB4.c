#include "common.h"
#include "shared/town_handler_entries.h"
short SD_Call(int flags);                     /* extern */
void call_the_handler_selects_nonzero_entry(); /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                  /* extern */
#include "shared/entity.h"
void update_actor_input_actions(void *context, EntityRec *entity, s32 update_arg);

/* Reset and initialize the record, then assign its handler. */
void initialize_action_object_and_play_sound(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x50B);
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D0110, record, setup_value);
    *record = &update_actor_input_actions;
}
