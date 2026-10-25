#include "common.h"
#include "town/player.h"

extern void clear_entity_record_fields(s32 record);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern u8 town_scene_record_handlers[];

extern s8 player_handler_reset_byte[16];

#include "town/player/initialize_record_with_handler_table_api.h"

/* Initialize the record, assign its handler table, and clear the first flag. */
void initialize_record_with_handler_table(Struct8009B1C8 *record, s32 setup_value, s32 init_value) {
    clear_entity_record_fields(setup_value);
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, record, init_value);
    record->unk4 = dispatch_state_callback_by_mode;
    player_handler_reset_byte[0] = 0;
}
